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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (char*) ; 

int main (int argc, char *argv[])
{
   FILE *fp;
   int res;
   long len;

   fp = fopen("testappend", "wb+");
   res = fwrite("1234567890", 10, 1, fp);
   fclose(fp);

   fp = fopen("testappend", "ab+");
   res = fwrite("1234567890", 10, 1, fp);

   fseek(fp, -7, SEEK_END);
   len = ftell(fp);
   assert(len == 13);
   fclose(fp);

   puts("success");
   return 0;
}