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
 int /*<<< orphan*/  SEEK_SET ; 
 int YabLoadStateStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (void const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tmpfile () ; 

int YabLoadStateBuffer(const void * buffer, size_t size)
{
   FILE * fp;
   int status;

   fp = tmpfile();
   fwrite(buffer, 1, size, fp);

   fseek(fp, 0, SEEK_SET);

   status = YabLoadStateStream(fp);
   fclose(fp);

   return status;
}