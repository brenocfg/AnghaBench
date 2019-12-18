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

/* Variables and functions */
 int dlg_editbox (char const*,char***,int*,int,int) ; 
 int /*<<< orphan*/  free_list (char***,int*) ; 
 int /*<<< orphan*/  load_list (char const*,char***,int*) ; 

int
dialog_editbox(const char *title, const char *file, int height, int width)
{
    int result;
    char **list;
    int rows;

    load_list(file, &list, &rows);
    result = dlg_editbox(title, &list, &rows, height, width);
    free_list(&list, &rows);
    return result;
}