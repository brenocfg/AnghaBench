#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  classes; int /*<<< orphan*/  names; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ metadata ;
typedef  int /*<<< orphan*/  list ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_labels (char*) ; 
 int /*<<< orphan*/  option_find_int (int /*<<< orphan*/ *,char*,int) ; 
 char* option_find_str (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_data_cfg (char*) ; 
 int /*<<< orphan*/  stderr ; 

metadata get_metadata(char *file)
{
    metadata m = {0};
    list *options = read_data_cfg(file);

    char *name_list = option_find_str(options, "names", 0);
    if(!name_list) name_list = option_find_str(options, "labels", 0);
    if(!name_list) {
        fprintf(stderr, "No names or labels found\n");
    } else {
        m.names = get_labels(name_list);
    }
    m.classes = option_find_int(options, "classes", 2);
    free_list(options);
    return m;
}