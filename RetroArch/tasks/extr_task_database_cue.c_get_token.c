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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  intfstream_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  EAGAIN 129 
#define  EINTR 128 
 int errno ; 
 scalar_t__ intfstream_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int64_t get_token(intfstream_t *fd, char *token, uint64_t max_len)
{
   char *c       = token;
   int64_t len   = 0;
   int in_string = 0;

   while (1)
   {
      int64_t rv = (int64_t)intfstream_read(fd, c, 1);
      if (rv == 0)
         return 0;

      if (rv < 1)
      {
         switch (errno)
         {
            case EINTR:
            case EAGAIN:
               continue;
            default:
               return -errno;
         }
      }

      switch (*c)
      {
         case ' ':
         case '\t':
         case '\r':
         case '\n':
            if (c == token)
               continue;

            if (!in_string)
            {
               *c = '\0';
               return len;
            }
            break;
         case '\"':
            if (c == token)
            {
               in_string = 1;
               continue;
            }

            *c = '\0';
            return len;
      }

      len++;
      c++;
      if (len == (int64_t)max_len)
      {
         *c = '\0';
         return len;
      }
   }
}