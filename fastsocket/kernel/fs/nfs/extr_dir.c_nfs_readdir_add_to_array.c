#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int dummy; } ;
struct nfs_entry {scalar_t__ eof; int /*<<< orphan*/  cookie; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  d_type; int /*<<< orphan*/  ino; int /*<<< orphan*/  prev_cookie; } ;
struct nfs_cache_array_entry {int /*<<< orphan*/  string; int /*<<< orphan*/  d_type; int /*<<< orphan*/  ino; int /*<<< orphan*/  cookie; } ;
struct nfs_cache_array {size_t size; size_t eof_index; int /*<<< orphan*/  last_cookie; struct nfs_cache_array_entry* array; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct nfs_cache_array*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct nfs_cache_array*) ; 
 struct nfs_cache_array* nfs_readdir_get_array (struct page*) ; 
 int nfs_readdir_make_qstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_readdir_release_array (struct page*) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static
int nfs_readdir_add_to_array(struct nfs_entry *entry, struct page *page)
{
	struct nfs_cache_array *array = nfs_readdir_get_array(page);
	struct nfs_cache_array_entry *cache_entry;
	int ret;

	if (IS_ERR(array))
		return PTR_ERR(array);

	cache_entry = &array->array[array->size];

	/* Check that this entry lies within the page bounds */
	ret = -ENOSPC;
	if ((char *)&cache_entry[1] - (char *)page_address(page) > PAGE_SIZE)
		goto out;

	cache_entry->cookie = entry->prev_cookie;
	cache_entry->ino = entry->ino;
	cache_entry->d_type = entry->d_type;
	ret = nfs_readdir_make_qstr(&cache_entry->string, entry->name, entry->len);
	if (ret)
		goto out;
	array->last_cookie = entry->cookie;
	array->size++;
	if (entry->eof != 0)
		array->eof_index = array->size;
out:
	nfs_readdir_release_array(page);
	return ret;
}