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
struct buffer_list {struct buffer_list* next; scalar_t__ buffer; } ;
struct buffer {size_t end_count; struct buffer_list* last; struct buffer_list first; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ERANGE ; 
 int MEMORY ; 
 int /*<<< orphan*/  assert (int) ; 
 struct buffer_list* buffer_extend (struct buffer_list*) ; 
 scalar_t__ errno ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 size_t fread (scalar_t__,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
buffer_from_file(struct buffer *buffer, FILE *fp)
{
   struct buffer_list *last = &buffer->first;
   size_t count = 0;

   for (;;)
   {
      size_t r = fread(last->buffer+count, 1/*size*/,
         (sizeof last->buffer)-count, fp);

      if (r > 0)
      {
         count += r;

         if (count >= sizeof last->buffer)
         {
            assert(count == sizeof last->buffer);
            count = 0;

            if (last->next == NULL)
            {
               last = buffer_extend(last);
               if (last == NULL)
                  return MEMORY;
            }

            else
               last = last->next;
         }
      }

      else /* fread failed - probably end of file */
      {
         if (feof(fp))
         {
            buffer->last = last;
            buffer->end_count = count;
            return 0; /* no error */
         }

         /* Some kind of funky error; errno should be non-zero */
         return errno == 0 ? ERANGE : errno;
      }
   }
}