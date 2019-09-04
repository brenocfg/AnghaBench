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
struct TYPE_3__ {unsigned long used; char** field; } ;
typedef  TYPE_1__ _bdf_list_t ;

/* Variables and functions */
 char* empty ; 

__attribute__((used)) static char *
  _bdf_list_join( _bdf_list_t*    list,
                  int             c,
                  unsigned long  *alen )
  {
    unsigned long  i, j;
    char           *fp, *dp;


    *alen = 0;

    if ( list == 0 || list->used == 0 )
      return 0;

    dp = list->field[0];
    for ( i = j = 0; i < list->used; i++ )
    {
      fp = list->field[i];
      while ( *fp )
        dp[j++] = *fp++;

      if ( i + 1 < list->used )
        dp[j++] = (char)c;
    }
    if ( dp != empty )
      dp[j] = 0;

    *alen = j;
    return dp;
  }