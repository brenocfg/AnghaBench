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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  link ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  string_parse_html_anchor (char const*,char*,char*,int,int) ; 

int main(int argc, char *argv[])
{
   char link[1024];
   char name[1024];
   const char *line  = "<a href=\"http://www.test.com/somefile.zip\">Test</a>\n";

   link[0] = name[0] = '\0';

   string_parse_html_anchor(line, link, name, sizeof(link), sizeof(name));

   printf("link: %s\nname: %s\n", link, name);

   return 1;
}