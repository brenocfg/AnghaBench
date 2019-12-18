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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ encoding; scalar_t__ codecid; } ;

/* Variables and functions */
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 TYPE_1__* codec_to_encoding_table ; 

__attribute__((used)) static uint32_t encoding_to_codecid(uint32_t encoding)
{
   unsigned int i;
   for(i = 0; codec_to_encoding_table[i].encoding != MMAL_ENCODING_UNKNOWN; i++)
      if(codec_to_encoding_table[i].encoding == encoding) break;
   return codec_to_encoding_table[i].codecid;
}