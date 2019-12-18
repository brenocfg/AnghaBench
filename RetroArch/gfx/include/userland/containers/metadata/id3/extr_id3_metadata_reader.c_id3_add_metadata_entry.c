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
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
struct TYPE_4__ {int size; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ VC_CONTAINER_METADATA_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_METADATA_KEY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*,unsigned int) ; 
 TYPE_1__* id3_metadata_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static VC_CONTAINER_METADATA_T *id3_add_metadata_entry( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_METADATA_KEY_T key, const char *value )
{
   VC_CONTAINER_METADATA_T *meta;
   unsigned int len = strlen(value);

   if ((meta = id3_metadata_append(p_ctx, key, len + 1)) != NULL)
   {
      unsigned int size = meta->size - 1;

      if (len > size)
      {
         LOG_DEBUG(p_ctx, "metadata value truncated (%d characters lost)", len - size);
      }

      strncpy(meta->value, value, size);
   }

   return meta;
}