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
 int /*<<< orphan*/  SEEK_SET ; 
 int YabSaveStateStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/ * tmpfile () ; 

int YabSaveStateBuffer(void ** buffer, size_t * size)
{
   FILE * fp;
   int status;
   size_t num_read = 0;

   if (buffer != NULL) *buffer = NULL;
   *size = 0;

   fp = tmpfile();

   status = YabSaveStateStream(fp);
   if (status != 0)
   {
      fclose(fp);
      return status;
   }

   fseek(fp, 0, SEEK_END);
   *size = ftell(fp);
   fseek(fp, 0, SEEK_SET);

   if (buffer != NULL)
   {
      *buffer = malloc(*size);
      num_read = fread(*buffer, 1, *size, fp);
   }

   fclose(fp);
   return 0;
}