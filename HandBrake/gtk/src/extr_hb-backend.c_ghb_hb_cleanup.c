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
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  del_tree (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hb_get_temporary_directory () ; 

void
ghb_hb_cleanup(gboolean partial)
{
    char * dir;

    dir = hb_get_temporary_directory();
    del_tree(dir, !partial);
    free(dir);
}