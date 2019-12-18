#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysv_dir_entry {char* name; int /*<<< orphan*/  inode; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {unsigned long i_size; struct super_block* i_sb; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {unsigned long f_pos; TYPE_2__ f_path; } ;
typedef  unsigned long loff_t ;
typedef  int (* filldir_t ) (void*,char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_UNKNOWN ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned long PAGE_CACHE_MASK ; 
 unsigned long PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 unsigned long SYSV_DIRSIZE ; 
 int /*<<< orphan*/  SYSV_NAMELEN ; 
 int /*<<< orphan*/  SYSV_SB (struct super_block*) ; 
 struct page* dir_get_page (struct inode*,unsigned long) ; 
 unsigned long dir_pages (struct inode*) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  fs16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  strnlen (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysv_readdir(struct file * filp, void * dirent, filldir_t filldir)
{
	unsigned long pos = filp->f_pos;
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct super_block *sb = inode->i_sb;
	unsigned offset = pos & ~PAGE_CACHE_MASK;
	unsigned long n = pos >> PAGE_CACHE_SHIFT;
	unsigned long npages = dir_pages(inode);

	pos = (pos + SYSV_DIRSIZE-1) & ~(SYSV_DIRSIZE-1);
	if (pos >= inode->i_size)
		goto done;

	for ( ; n < npages; n++, offset = 0) {
		char *kaddr, *limit;
		struct sysv_dir_entry *de;
		struct page *page = dir_get_page(inode, n);

		if (IS_ERR(page))
			continue;
		kaddr = (char *)page_address(page);
		de = (struct sysv_dir_entry *)(kaddr+offset);
		limit = kaddr + PAGE_CACHE_SIZE - SYSV_DIRSIZE;
		for ( ;(char*)de <= limit; de++) {
			char *name = de->name;
			int over;

			if (!de->inode)
				continue;

			offset = (char *)de - kaddr;

			over = filldir(dirent, name, strnlen(name,SYSV_NAMELEN),
					((loff_t)n<<PAGE_CACHE_SHIFT) | offset,
					fs16_to_cpu(SYSV_SB(sb), de->inode),
					DT_UNKNOWN);
			if (over) {
				dir_put_page(page);
				goto done;
			}
		}
		dir_put_page(page);
	}

done:
	filp->f_pos = ((loff_t)n << PAGE_CACHE_SHIFT) | offset;
	return 0;
}