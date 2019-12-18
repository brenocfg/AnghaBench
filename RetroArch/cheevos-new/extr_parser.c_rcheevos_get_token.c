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
 int /*<<< orphan*/  CHEEVOS_JSON_KEY_ERROR ; 
 int /*<<< orphan*/  CHEEVOS_JSON_KEY_TOKEN ; 
 int rcheevos_get_value (char const*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 

int rcheevos_get_token(const char* json, char* token, size_t length)
{
   rcheevos_get_value(json, CHEEVOS_JSON_KEY_ERROR, token, length);

   if (!string_is_empty(token))
      return -1;

   return rcheevos_get_value(json, CHEEVOS_JSON_KEY_TOKEN, token, length);
}