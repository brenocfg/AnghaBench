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
typedef  int /*<<< orphan*/  word ;
struct file_data {size_t buffered; int missing_newline; } ;

/* Variables and functions */
 char* FILE_BUFFER (struct file_data*) ; 
 char* memchr (char*,char,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strip_trailing_cr ; 

__attribute__((used)) static void
prepare_text (struct file_data *current)
{
  size_t buffered = current->buffered;
  char *p = FILE_BUFFER (current);
  char *dst;

  if (buffered == 0 || p[buffered - 1] == '\n')
    current->missing_newline = false;
  else
    {
      p[buffered++] = '\n';
      current->missing_newline = true;
    }

  if (!p)
    return;

  /* Don't use uninitialized storage when planting or using sentinels.  */
  memset (p + buffered, 0, sizeof (word));

  if (strip_trailing_cr && (dst = memchr (p, '\r', buffered)))
    {
      char const *src = dst;
      char const *srclim = p + buffered;

      do
	dst += ! ((*dst = *src++) == '\r' && *src == '\n');
      while (src < srclim);

      buffered -= src - dst;
    }

  current->buffered = buffered;
}