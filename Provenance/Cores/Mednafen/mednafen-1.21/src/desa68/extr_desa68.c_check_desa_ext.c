#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int w; char reg0; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 

__attribute__((used)) static int check_desa_ext()
{
  if((d.w&07670)!=04200)
    return 0;
  desa_ascii('EXT.' );
  desa_ascii((!(d.w&0100)? 'W D0':'L D0') + d.reg0);
  return 1;
}