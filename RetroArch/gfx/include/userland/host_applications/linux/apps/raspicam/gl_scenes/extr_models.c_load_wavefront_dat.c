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
struct wavefront_model_loading_s {int dummy; } ;
typedef  int /*<<< orphan*/  WAVEFRONT_MODEL_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_VERTICES ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (struct wavefront_model_loading_s*,int,int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int load_wavefront_dat(const char *modelname, WAVEFRONT_MODEL_T *model, struct wavefront_model_loading_s *m)
{
   FILE *fp;
   int s;
   const int size = sizeof *m +
      sizeof(float)*(3+2+3)*MAX_VERTICES +   // 3 vertices + 2 textures + 3 normals
      sizeof(unsigned short)*3*MAX_VERTICES; //each face has 9 vertices

   fp = fopen(modelname, "r");
   if (!fp) return -1;
   s = fread(m, 1, size, fp);
   if (s < 0) return -1;
   fclose(fp);
   return 0;
}