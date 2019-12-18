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
struct pohmelfs_crypto_engine {int /*<<< orphan*/  iv; } ;
struct pohmelfs_crypto_thread {int /*<<< orphan*/  size; struct page* page; struct pohmelfs_crypto_engine eng; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageChecked (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int pohmelfs_crypto_process_input_data (struct pohmelfs_crypto_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pohmelfs_crypto_thread_make_ready (struct pohmelfs_crypto_thread*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int pohmelfs_crypto_thread_page(struct pohmelfs_crypto_thread *t)
{
	struct pohmelfs_crypto_engine *e = &t->eng;
	struct page *page = t->page;
	int err;

	WARN_ON(!PageChecked(page));

	err = pohmelfs_crypto_process_input_data(e, e->iv, NULL, page, t->size);
	if (!err)
		SetPageUptodate(page);
	else
		SetPageError(page);
	unlock_page(page);
	page_cache_release(page);

	pohmelfs_crypto_thread_make_ready(t);

	return err;
}