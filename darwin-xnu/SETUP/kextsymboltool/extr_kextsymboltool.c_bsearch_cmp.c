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
struct symbol {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bsearch_cmp( const void * _key, const void * _cmp)
{
    char * key = (char *)_key;
    struct symbol * cmp = (struct symbol *) _cmp;

    return(strcmp(key, cmp->name));
}