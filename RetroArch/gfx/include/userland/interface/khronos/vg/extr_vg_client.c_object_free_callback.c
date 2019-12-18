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
typedef  void* uint32_t ;
typedef  void KHRN_POINTER_MAP_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  object_free (void*) ; 

__attribute__((used)) static void object_free_callback(KHRN_POINTER_MAP_T *pointer_map, uint32_t key, void *object, void *data)
{
   UNUSED(pointer_map);
   UNUSED(key);
   UNUSED(data);

   object_free(object);
}