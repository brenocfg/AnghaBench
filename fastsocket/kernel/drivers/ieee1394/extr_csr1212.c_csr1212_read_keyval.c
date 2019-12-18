#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct csr1212_keyval_img {int /*<<< orphan*/  length; } ;
struct TYPE_7__ {int len; int* data; } ;
struct TYPE_8__ {TYPE_3__ leaf; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct csr1212_keyval {int offset; TYPE_4__ value; TYPE_1__ key; } ;
struct csr1212_csr_rom_cache {int offset; int size; int* data; struct csr1212_cache_region* filled_head; struct csr1212_cache_region* filled_tail; struct csr1212_csr_rom_cache* next; struct csr1212_csr_rom_cache* prev; } ;
struct csr1212_csr {int max_rom; int /*<<< orphan*/  private; TYPE_2__* ops; struct csr1212_csr_rom_cache* cache_tail; struct csr1212_csr_rom_cache* cache_head; } ;
struct csr1212_cache_region {int offset_start; int offset_end; struct csr1212_cache_region* prev; struct csr1212_cache_region* next; } ;
struct TYPE_6__ {scalar_t__ (* bus_read ) (struct csr1212_csr*,int,int*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CSR1212_CSR_ARCH_REG_SPACE_BASE ; 
 int /*<<< orphan*/  CSR1212_FREE (struct csr1212_cache_region*) ; 
 scalar_t__ CSR1212_KV_ID_EXTENDED_ROM ; 
 void* CSR1212_MALLOC (int) ; 
 int CSR1212_REGISTER_SPACE_BASE ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int) ; 
 size_t bytes_to_quads (int) ; 
 int csr1212_parse_keyval (struct csr1212_keyval*,struct csr1212_csr_rom_cache*) ; 
 struct csr1212_csr_rom_cache* csr1212_rom_cache_malloc (int,int) ; 
 int quads_to_bytes (int) ; 
 scalar_t__ stub1 (struct csr1212_csr*,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct csr1212_csr*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csr1212_read_keyval(struct csr1212_csr *csr, struct csr1212_keyval *kv)
{
	struct csr1212_cache_region *cr, *ncr, *newcr = NULL;
	struct csr1212_keyval_img *kvi = NULL;
	struct csr1212_csr_rom_cache *cache;
	int cache_index;
	u64 addr;
	u32 *cache_ptr;
	u16 kv_len = 0;

	BUG_ON(!csr || !kv || csr->max_rom < 1);

	/* First find which cache the data should be in (or go in if not read
	 * yet). */
	for (cache = csr->cache_head; cache; cache = cache->next)
		if (kv->offset >= cache->offset &&
		    kv->offset < (cache->offset + cache->size))
			break;

	if (!cache) {
		u32 q, cache_size;

		/* Only create a new cache for Extended ROM leaves. */
		if (kv->key.id != CSR1212_KV_ID_EXTENDED_ROM)
			return -EINVAL;

		if (csr->ops->bus_read(csr,
				       CSR1212_REGISTER_SPACE_BASE + kv->offset,
				       &q, csr->private))
			return -EIO;

		kv->value.leaf.len = be32_to_cpu(q) >> 16;

		cache_size = (quads_to_bytes(kv->value.leaf.len + 1) +
			      (csr->max_rom - 1)) & ~(csr->max_rom - 1);

		cache = csr1212_rom_cache_malloc(kv->offset, cache_size);
		if (!cache)
			return -ENOMEM;

		kv->value.leaf.data = &cache->data[1];
		csr->cache_tail->next = cache;
		cache->prev = csr->cache_tail;
		cache->next = NULL;
		csr->cache_tail = cache;
		cache->filled_head =
			CSR1212_MALLOC(sizeof(*cache->filled_head));
		if (!cache->filled_head)
			return -ENOMEM;

		cache->filled_head->offset_start = 0;
		cache->filled_head->offset_end = sizeof(u32);
		cache->filled_tail = cache->filled_head;
		cache->filled_head->next = NULL;
		cache->filled_head->prev = NULL;
		cache->data[0] = q;

		/* Don't read the entire extended ROM now.  Pieces of it will
		 * be read when entries inside it are read. */
		return csr1212_parse_keyval(kv, cache);
	}

	cache_index = kv->offset - cache->offset;

	/* Now seach read portions of the cache to see if it is there. */
	for (cr = cache->filled_head; cr; cr = cr->next) {
		if (cache_index < cr->offset_start) {
			newcr = CSR1212_MALLOC(sizeof(*newcr));
			if (!newcr)
				return -ENOMEM;

			newcr->offset_start = cache_index & ~(csr->max_rom - 1);
			newcr->offset_end = newcr->offset_start;
			newcr->next = cr;
			newcr->prev = cr->prev;
			cr->prev = newcr;
			cr = newcr;
			break;
		} else if ((cache_index >= cr->offset_start) &&
			   (cache_index < cr->offset_end)) {
			kvi = (struct csr1212_keyval_img*)
				(&cache->data[bytes_to_quads(cache_index)]);
			kv_len = quads_to_bytes(be16_to_cpu(kvi->length) + 1);
			break;
		} else if (cache_index == cr->offset_end) {
			break;
		}
	}

	if (!cr) {
		cr = cache->filled_tail;
		newcr = CSR1212_MALLOC(sizeof(*newcr));
		if (!newcr)
			return -ENOMEM;

		newcr->offset_start = cache_index & ~(csr->max_rom - 1);
		newcr->offset_end = newcr->offset_start;
		newcr->prev = cr;
		newcr->next = cr->next;
		cr->next = newcr;
		cr = newcr;
		cache->filled_tail = newcr;
	}

	while(!kvi || cr->offset_end < cache_index + kv_len) {
		cache_ptr = &cache->data[bytes_to_quads(cr->offset_end &
							~(csr->max_rom - 1))];

		addr = (CSR1212_CSR_ARCH_REG_SPACE_BASE + cache->offset +
			cr->offset_end) & ~(csr->max_rom - 1);

		if (csr->ops->bus_read(csr, addr, cache_ptr, csr->private))
			return -EIO;

		cr->offset_end += csr->max_rom - (cr->offset_end &
						  (csr->max_rom - 1));

		if (!kvi && (cr->offset_end > cache_index)) {
			kvi = (struct csr1212_keyval_img*)
				(&cache->data[bytes_to_quads(cache_index)]);
			kv_len = quads_to_bytes(be16_to_cpu(kvi->length) + 1);
		}

		if ((kv_len + (kv->offset - cache->offset)) > cache->size) {
			/* The Leaf or Directory claims its length extends
			 * beyond the ConfigROM image region and thus beyond the
			 * end of our cache region.  Therefore, we abort now
			 * rather than seg faulting later. */
			return -EIO;
		}

		ncr = cr->next;

		if (ncr && (cr->offset_end >= ncr->offset_start)) {
			/* consolidate region entries */
			ncr->offset_start = cr->offset_start;

			if (cr->prev)
				cr->prev->next = cr->next;
			ncr->prev = cr->prev;
			if (cache->filled_head == cr)
				cache->filled_head = ncr;
			CSR1212_FREE(cr);
			cr = ncr;
		}
	}

	return csr1212_parse_keyval(kv, cache);
}