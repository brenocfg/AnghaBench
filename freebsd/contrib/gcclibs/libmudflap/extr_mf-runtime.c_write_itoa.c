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
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_itoa (int fd, unsigned n)
{
  enum x { bufsize = sizeof(n)*4 };
  char buf [bufsize];
  unsigned i;

  for (i=0; i<bufsize-1; i++)
    {
      unsigned digit = n % 10;
      buf[bufsize-2-i] = digit + '0';
      n /= 10;
      if (n == 0)
        {
          char *m = & buf [bufsize-2-i];
          buf[bufsize-1] = '\0';
          write (fd, m, strlen(m));
          break;
        }
    }
}