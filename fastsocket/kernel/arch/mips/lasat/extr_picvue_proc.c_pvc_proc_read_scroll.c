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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvc_mutex ; 
 int scroll_dir ; 
 int scroll_interval ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int pvc_proc_read_scroll(char *page, char **start,
			     off_t off, int count,
			     int *eof, void *data)
{
	char *origpage = page;

	mutex_lock(&pvc_mutex);
	page += sprintf(page, "%d\n", scroll_dir * scroll_interval);
	mutex_unlock(&pvc_mutex);

	return page - origpage;
}