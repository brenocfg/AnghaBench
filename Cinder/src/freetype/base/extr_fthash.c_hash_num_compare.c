#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num; } ;
typedef  TYPE_1__ FT_Hashkey ;
typedef  int FT_Bool ;

/* Variables and functions */

__attribute__((used)) static FT_Bool
  hash_num_compare( FT_Hashkey*  a,
                    FT_Hashkey*  b )
  {
    if ( a->num == b->num )
      return 1;

    return 0;
  }