#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct page {int index; TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_20__ {TYPE_6__* base_ntfs_ino; } ;
struct TYPE_24__ {scalar_t__ type; int name_len; int initialized_size; int /*<<< orphan*/  size_lock; int /*<<< orphan*/  name; TYPE_2__ ext; } ;
typedef  TYPE_6__ ntfs_inode ;
struct TYPE_25__ {TYPE_5__* attr; } ;
typedef  TYPE_7__ ntfs_attr_search_ctx ;
typedef  int loff_t ;
struct TYPE_21__ {int /*<<< orphan*/  value_offset; int /*<<< orphan*/  value_length; } ;
struct TYPE_22__ {TYPE_3__ resident; } ;
struct TYPE_23__ {TYPE_4__ data; } ;
struct TYPE_19__ {struct inode* host; } ;
typedef  int /*<<< orphan*/  MFT_RECORD ;

/* Variables and functions */
 scalar_t__ AT_DATA ; 
 scalar_t__ AT_INDEX_ALLOCATION ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CASE_SENSITIVE ; 
 int EACCES ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  NInoAttr (TYPE_6__*) ; 
 scalar_t__ NInoCompressed (TYPE_6__*) ; 
 scalar_t__ NInoEncrypted (TYPE_6__*) ; 
 int NInoNonResident (TYPE_6__*) ; 
 TYPE_6__* NTFS_I (struct inode*) ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/ * kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_mft_record (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* ntfs_attr_get_search_ctx (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int ntfs_attr_lookup (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ntfs_attr_put_search_ctx (TYPE_7__*) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int ntfs_read_block (struct page*) ; 
 int ntfs_read_compressed_block (struct page*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  unmap_mft_record (TYPE_6__*) ; 
 int /*<<< orphan*/  zero_user (struct page*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ntfs_readpage(struct file *file, struct page *page)
{
	loff_t i_size;
	struct inode *vi;
	ntfs_inode *ni, *base_ni;
	u8 *addr;
	ntfs_attr_search_ctx *ctx;
	MFT_RECORD *mrec;
	unsigned long flags;
	u32 attr_len;
	int err = 0;

retry_readpage:
	BUG_ON(!PageLocked(page));
	vi = page->mapping->host;
	i_size = i_size_read(vi);
	/* Is the page fully outside i_size? (truncate in progress) */
	if (unlikely(page->index >= (i_size + PAGE_CACHE_SIZE - 1) >>
			PAGE_CACHE_SHIFT)) {
		zero_user(page, 0, PAGE_CACHE_SIZE);
		ntfs_debug("Read outside i_size - truncated?");
		goto done;
	}
	/*
	 * This can potentially happen because we clear PageUptodate() during
	 * ntfs_writepage() of MstProtected() attributes.
	 */
	if (PageUptodate(page)) {
		unlock_page(page);
		return 0;
	}
	ni = NTFS_I(vi);
	/*
	 * Only $DATA attributes can be encrypted and only unnamed $DATA
	 * attributes can be compressed.  Index root can have the flags set but
	 * this means to create compressed/encrypted files, not that the
	 * attribute is compressed/encrypted.  Note we need to check for
	 * AT_INDEX_ALLOCATION since this is the type of both directory and
	 * index inodes.
	 */
	if (ni->type != AT_INDEX_ALLOCATION) {
		/* If attribute is encrypted, deny access, just like NT4. */
		if (NInoEncrypted(ni)) {
			BUG_ON(ni->type != AT_DATA);
			err = -EACCES;
			goto err_out;
		}
		/* Compressed data streams are handled in compress.c. */
		if (NInoNonResident(ni) && NInoCompressed(ni)) {
			BUG_ON(ni->type != AT_DATA);
			BUG_ON(ni->name_len);
			return ntfs_read_compressed_block(page);
		}
	}
	/* NInoNonResident() == NInoIndexAllocPresent() */
	if (NInoNonResident(ni)) {
		/* Normal, non-resident data stream. */
		return ntfs_read_block(page);
	}
	/*
	 * Attribute is resident, implying it is not compressed or encrypted.
	 * This also means the attribute is smaller than an mft record and
	 * hence smaller than a page, so can simply zero out any pages with
	 * index above 0.  Note the attribute can actually be marked compressed
	 * but if it is resident the actual data is not compressed so we are
	 * ok to ignore the compressed flag here.
	 */
	if (unlikely(page->index > 0)) {
		zero_user(page, 0, PAGE_CACHE_SIZE);
		goto done;
	}
	if (!NInoAttr(ni))
		base_ni = ni;
	else
		base_ni = ni->ext.base_ntfs_ino;
	/* Map, pin, and lock the mft record. */
	mrec = map_mft_record(base_ni);
	if (IS_ERR(mrec)) {
		err = PTR_ERR(mrec);
		goto err_out;
	}
	/*
	 * If a parallel write made the attribute non-resident, drop the mft
	 * record and retry the readpage.
	 */
	if (unlikely(NInoNonResident(ni))) {
		unmap_mft_record(base_ni);
		goto retry_readpage;
	}
	ctx = ntfs_attr_get_search_ctx(base_ni, mrec);
	if (unlikely(!ctx)) {
		err = -ENOMEM;
		goto unm_err_out;
	}
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, NULL, 0, ctx);
	if (unlikely(err))
		goto put_unm_err_out;
	attr_len = le32_to_cpu(ctx->attr->data.resident.value_length);
	read_lock_irqsave(&ni->size_lock, flags);
	if (unlikely(attr_len > ni->initialized_size))
		attr_len = ni->initialized_size;
	i_size = i_size_read(vi);
	read_unlock_irqrestore(&ni->size_lock, flags);
	if (unlikely(attr_len > i_size)) {
		/* Race with shrinking truncate. */
		attr_len = i_size;
	}
	addr = kmap_atomic(page, KM_USER0);
	/* Copy the data to the page. */
	memcpy(addr, (u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset),
			attr_len);
	/* Zero the remainder of the page. */
	memset(addr + attr_len, 0, PAGE_CACHE_SIZE - attr_len);
	flush_dcache_page(page);
	kunmap_atomic(addr, KM_USER0);
put_unm_err_out:
	ntfs_attr_put_search_ctx(ctx);
unm_err_out:
	unmap_mft_record(base_ni);
done:
	SetPageUptodate(page);
err_out:
	unlock_page(page);
	return err;
}