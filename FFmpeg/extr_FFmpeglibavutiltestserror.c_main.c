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
struct error_entry {int num; char* tag; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (struct error_entry*) ; 
 char* av_err2str (int) ; 
 struct error_entry* error_entries ; 
 int /*<<< orphan*/  printf (char*,int,char*,...) ; 

int main(void)
{
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(error_entries); i++) {
        const struct error_entry *entry = &error_entries[i];
        printf("%d: %s [%s]\n", entry->num, av_err2str(entry->num), entry->tag);
    }

    for (i = 0; i < 256; i++) {
        printf("%d: %s\n", -i, av_err2str(-i));
    }

    return 0;
}