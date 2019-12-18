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
struct tfile_check {scalar_t__ count; struct tfile_check* next; struct epoll_filefd** tfile_arr; } ;
struct epoll_filefd {int added; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NUM_FILES ; 
 struct tfile_check* current_tfile_check ; 
 struct tfile_check* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_to_tfile_check(struct epoll_filefd *ffd)
{
	struct tfile_check *new;

	if (current_tfile_check->count < NUM_FILES) {
		current_tfile_check->tfile_arr[current_tfile_check->count++] = ffd;
		ffd->added = 1;
		return 0;
	}
	new = kmalloc(sizeof(struct tfile_check), GFP_KERNEL);
	if (!new)
		return -ENOMEM;
	new->count = 0;
	new->next = NULL;
	new->tfile_arr[new->count++] = ffd;
	ffd->added = 1;
	current_tfile_check->next = new;
	current_tfile_check = new;

	return 0;
}