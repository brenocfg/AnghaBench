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
struct print_file_list {unsigned int maxline; char** linemap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcspn (char const*,char*) ; 

__attribute__((used)) static void 
print_line (struct print_file_list *p, unsigned int line)
{
  const char *l;
 
  --line; 
  if (line >= p->maxline)
    return;
  l = p->linemap [line];
  fwrite (l, 1, strcspn (l, "\n\r"), stdout);
  putchar ('\n');
}