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
typedef  scalar_t__ VC_CONTAINER_METADATA_KEY_T ;
struct TYPE_2__ {scalar_t__ key; char const* name; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_METADATA_KEY_UNKNOWN ; 
 TYPE_1__* meta_key_conv ; 

const char *vc_container_metadata_id_to_string(VC_CONTAINER_METADATA_KEY_T key)
{
   int i;
   for(i = 0; meta_key_conv[i].key != VC_CONTAINER_METADATA_KEY_UNKNOWN; i++ )
      if(meta_key_conv[i].key == key) break;
   return meta_key_conv[i].name;
}