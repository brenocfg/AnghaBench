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
typedef  int /*<<< orphan*/  list ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 char* option_find (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 

int option_find_int(list *l, char *key, int def)
{
    char *v = option_find(l, key);
    if(v) return atoi(v);
    fprintf(stderr, "%s: Using default '%d'\n", key, def);
    return def;
}