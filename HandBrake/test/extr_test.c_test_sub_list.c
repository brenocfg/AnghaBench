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
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_sub_list( char ** list, int pos )
{
    int i;

    if ( list == NULL || pos == 0 )
        return 0;

    if ( list[0] == NULL && pos == 1 )
        return 1;

    for ( i = 0; list[i] != NULL; i++ )
    {
        int idx = strtol( list[i], NULL, 0 );
        if ( idx == pos )
            return 1;
    }
    return 0;
}