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
struct file_list {char* f_extra; struct file_list* f_next; scalar_t__ f_type; scalar_t__ f_flags; scalar_t__ f_needs; } ;

/* Variables and functions */
 struct file_list* fcur ; 
 struct file_list* ftab ; 
 scalar_t__ malloc (int) ; 

struct file_list *
new_fent(void)
{
	struct file_list *fp;

	fp = (struct file_list *) malloc(sizeof *fp);
	fp->f_needs = 0;
	fp->f_next = 0;
	fp->f_flags = 0;
	fp->f_type = 0;
	fp->f_extra = (char *) 0;
	if (fcur == 0)
		fcur = ftab = fp;
	else
		fcur->f_next = fp;
	fcur = fp;
	return (fp);
}