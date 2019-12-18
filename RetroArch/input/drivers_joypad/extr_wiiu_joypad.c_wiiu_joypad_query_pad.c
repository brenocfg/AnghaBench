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
struct TYPE_2__ {scalar_t__ (* query_pad ) (unsigned int) ;} ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
 TYPE_1__** pad_drivers ; 
 scalar_t__ ready ; 
 scalar_t__ stub1 (unsigned int) ; 

__attribute__((used)) static bool wiiu_joypad_query_pad(unsigned pad)
{
   return ready                &&
      pad < MAX_USERS          &&
      pad_drivers[pad] != NULL &&
      pad_drivers[pad]->query_pad(pad);
}