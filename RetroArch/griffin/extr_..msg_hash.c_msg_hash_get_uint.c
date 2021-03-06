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
typedef  enum msg_hash_action { ____Placeholder_msg_hash_action } msg_hash_action ;

/* Variables and functions */
#define  MSG_HASH_NONE 129 
#define  MSG_HASH_USER_LANGUAGE 128 
 unsigned int uint_user_language ; 

unsigned *msg_hash_get_uint(enum msg_hash_action type)
{
   switch (type)
   {
      case MSG_HASH_USER_LANGUAGE:
         return &uint_user_language;
      case MSG_HASH_NONE:
         break;
   }

   return NULL;
}