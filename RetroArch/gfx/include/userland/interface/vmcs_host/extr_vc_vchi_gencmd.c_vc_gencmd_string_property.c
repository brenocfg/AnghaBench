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
#define  READING_PROPERTY 130 
#define  READING_VALUE 129 
#define  READING_VALUE_QUOTED 128 
 int /*<<< orphan*/  isspace (int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t) ; 

int vc_gencmd_string_property(char *text, const char *property, char **value, int *length) {
#define READING_PROPERTY 0
#define READING_VALUE 1
#define READING_VALUE_QUOTED 2
   int state = READING_PROPERTY;
   int delimiter = 1, match = 0, len = (int)strlen(property);
   char *prop_start=text, *value_start=text;
   for (; *text; text++) {
      int ch = *text;
      switch (state) {
      case READING_PROPERTY:
         if (delimiter) prop_start = text;
         if (isspace(ch)) delimiter = 1;
         else if (ch == '=') {
            delimiter = 1;
            match = (text-prop_start==len && strncmp(prop_start, property, (size_t)(text-prop_start))==0);
            state = READING_VALUE;
         }
         else delimiter = 0;
         break;
      case READING_VALUE:
         if (delimiter) value_start = text;
         if (isspace(ch)) {
            if (match) goto success;
            delimiter = 1;
            state = READING_PROPERTY;
         }
         else if (delimiter && ch == '"') {
            delimiter = 1;
            state = READING_VALUE_QUOTED;
         }
         else delimiter = 0;
         break;
      case READING_VALUE_QUOTED:
         if (delimiter) value_start = text;
         if (ch == '"') {
            if (match) goto success;
            delimiter = 1;
            state = READING_PROPERTY;
         }
         else delimiter = 0;
         break;
      }
   }
   if (match) goto success;
   return 0;
success:
   *value = value_start;
   *length = text - value_start;
   return 1;
}