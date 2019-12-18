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
 scalar_t__ malloc (size_t) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

char* string_tokenize(char **str, const char *delim)
{
   /* Taken from https://codereview.stackexchange.com/questions/216956/strtok-function-thread-safe-supports-empty-tokens-doesnt-change-string# */
   char *str_ptr    = NULL;
   char *delim_ptr  = NULL;
   char *token      = NULL;
   size_t token_len = 0;

   /* Sanity checks */
   if (!str || string_is_empty(delim))
      return NULL;

   str_ptr = *str;

   /* Note: we don't check string_is_empty() here,
    * empty strings are valid */
   if (!str_ptr)
      return NULL;

   /* Search for delimiter */
   delim_ptr = strstr(str_ptr, delim);

   if (delim_ptr)
      token_len = delim_ptr - str_ptr;
   else
      token_len = strlen(str_ptr);

   /* Allocate token string */
   token = (char *)malloc((token_len + 1) * sizeof(char));

   if (!token)
      return NULL;

   /* Copy token */
   strlcpy(token, str_ptr, (token_len + 1) * sizeof(char));
   token[token_len] = '\0';

   /* Update input string pointer */
   *str = delim_ptr ? delim_ptr + strlen(delim) : NULL;

   return token;
}