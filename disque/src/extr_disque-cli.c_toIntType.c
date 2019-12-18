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
 int TYPE_HASH ; 
 int TYPE_LIST ; 
 int TYPE_NONE ; 
 int TYPE_SET ; 
 int TYPE_STRING ; 
 int TYPE_ZSET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int toIntType(char *key, char *type) {
    if(!strcmp(type, "string")) {
        return TYPE_STRING;
    } else if(!strcmp(type, "list")) {
        return TYPE_LIST;
    } else if(!strcmp(type, "set")) {
        return TYPE_SET;
    } else if(!strcmp(type, "hash")) {
        return TYPE_HASH;
    } else if(!strcmp(type, "zset")) {
        return TYPE_ZSET;
    } else if(!strcmp(type, "none")) {
        return TYPE_NONE;
    } else {
        fprintf(stderr, "Unknown type '%s' for key '%s'\n", type, key);
        exit(1);
    }
}