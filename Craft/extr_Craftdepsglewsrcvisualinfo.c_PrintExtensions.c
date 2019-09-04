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
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void PrintExtensions (const char* s)
{
  char t[80];
  int i=0;
  char* p=0;

  t[79] = '\0';
  while (*s)
  {
    t[i++] = *s;
    if(*s == ' ')
    {
      if (*(s+1) != '\0') {
	t[i-1] = ',';
	t[i] = ' ';
	p = &t[i++];
      }
      else /* zoinks! last one terminated in a space! */
      {
	t[i-1] = '\0';
      }
    }
    if(i > 80 - 5)
    {
      *p = t[i] = '\0';
      fprintf(file, "    %s\n", t);
      p++;
      i = (int)strlen(p);
      strcpy(t, p);
    }
    s++;
  }
  t[i] = '\0';
  fprintf(file, "    %s.\n", t);
}