#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct xdr_buf {unsigned int page_len; unsigned int buflen; unsigned int len; struct page** pages; } ;
struct page {int dummy; } ;
struct nfs_entry {scalar_t__ eof; } ;
struct nfs_cache_array {int /*<<< orphan*/  size; int /*<<< orphan*/  eof_index; } ;
struct TYPE_8__ {scalar_t__ plus; TYPE_2__* file; } ;
typedef  TYPE_3__ nfs_readdir_descriptor_t ;
struct TYPE_6__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_7__ {TYPE_1__ f_path; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADCOOKIE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct nfs_cache_array*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct nfs_cache_array*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_prime_dcache (int /*<<< orphan*/ ,struct nfs_entry*) ; 
 int nfs_readdir_add_to_array (struct nfs_entry*,struct page*) ; 
 struct nfs_cache_array* nfs_readdir_get_array (struct page*) ; 
 int /*<<< orphan*/  nfs_readdir_release_array (struct page*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int xdr_decode (TYPE_3__*,struct nfs_entry*,struct xdr_stream*) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,struct xdr_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_set_scratch_buffer (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int nfs_readdir_page_filler(nfs_readdir_descriptor_t *desc, struct nfs_entry *entry,
				struct page **xdr_pages, struct page *page, unsigned int buflen)
{
	struct xdr_stream stream;
	struct xdr_buf buf = {
		.pages = xdr_pages,
		.page_len = buflen,
		.buflen = buflen,
		.len = buflen,
	};
	struct page *scratch;
	struct nfs_cache_array *array;
	unsigned int count = 0;
	int status;

	scratch = alloc_page(GFP_KERNEL);
	if (scratch == NULL)
		return -ENOMEM;

	xdr_init_decode(&stream, &buf, NULL);
	xdr_set_scratch_buffer(&stream, page_address(scratch), PAGE_SIZE);

	do {
		status = xdr_decode(desc, entry, &stream);
		if (status != 0) {
			if (status == -EAGAIN)
				status = 0;
			break;
		}

		count++;

		if (desc->plus != 0)
			nfs_prime_dcache(desc->file->f_path.dentry, entry);

		status = nfs_readdir_add_to_array(entry, page);
		if (status != 0)
			break;
	} while (!entry->eof);

	if (count == 0 || (status == -EBADCOOKIE && entry->eof != 0)) {
		array = nfs_readdir_get_array(page);
		if (!IS_ERR(array)) {
			array->eof_index = array->size;
			status = 0;
			nfs_readdir_release_array(page);
		} else
			status = PTR_ERR(array);
	}

	put_page(scratch);
	return status;
}