#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x_vector; int y_vector; } ;
typedef  TYPE_1__ INLINE_MOTION_VECTOR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 unsigned char floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  fputc (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (char*,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sqrt (int) ; 

int main(int argc, const char **argv)
{
   if(argc!=5)
   {
      printf("usage: %s data.imv mbx mby out.pgm\n",argv[0]);
      return 0;
   }
   int mbx=atoi(argv[2]);
   int mby=atoi(argv[3]);

   ///////////////////////////////
   //  Read raw file to buffer  //
   ///////////////////////////////
   FILE *f = fopen(argv[1], "rb");
   fseek(f, 0, SEEK_END);
   long fsize = ftell(f);
   fseek(f, 0, SEEK_SET);
   char *buffer = malloc(fsize + 1);
   fread(buffer, fsize, 1, f);
   fclose(f);
   buffer[fsize] = 0;

   ///////////////////
   //  Fill struct  //
   ///////////////////
   if(fsize<(mbx+1)*mby*4)
   {
      printf("File to short!\n");
      return 0;
   }
   INLINE_MOTION_VECTOR *imv;
   imv = malloc((mbx+1)*mby*sizeof(INLINE_MOTION_VECTOR));
   memcpy ( &imv[0], &buffer[0], (mbx+1)*mby*sizeof(INLINE_MOTION_VECTOR) );

   /////////////////////
   //  Export to PGM  //
   /////////////////////
   FILE *out = fopen(argv[4], "w");
   fprintf(out,"P5\n%d %d\n255\n",mbx,mby);
   int i,j;
   for(j=0;j<mby; j++)
      for(i=0;i<mbx; i++)
   {
         unsigned char magU=floor(sqrt(imv[i+(mbx+1)*j].x_vector*imv[i+(mbx+1)*j].x_vector+imv[i+(mbx+1)*j].y_vector*imv[i+(mbx+1)*j].y_vector));
         fputc(magU,out);
   }
   fclose(out);
 return 0;

}