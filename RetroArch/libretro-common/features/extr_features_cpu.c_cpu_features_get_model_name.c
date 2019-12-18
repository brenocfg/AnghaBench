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
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_cpuid (int,int*) ; 

void cpu_features_get_model_name(char *name, int len)
{
#if defined(CPU_X86) && !defined(__MACH__)
   union {
      int i[4];
      unsigned char s[16];
   } flags;
   int i, j;
   size_t pos = 0;
   bool start = false;

   if (!name)
      return;

   x86_cpuid(0x80000000, flags.i);

   if (flags.i[0] < 0x80000004)
      return;

   for (i = 0; i < 3; i++)
   {
      memset(flags.i, 0, sizeof(flags.i));
      x86_cpuid(0x80000002 + i, flags.i);

      for (j = 0; j < sizeof(flags.s); j++)
      {
         if (!start && flags.s[j] == ' ')
            continue;
         else
            start = true;

         if (pos == len - 1)
         {
            /* truncate if we ran out of room */
            name[pos] = '\0';
            goto end;
         }

         name[pos++] = flags.s[j];
      }
   }
end:
   /* terminate our string */
   if (pos < (size_t)len)
      name[pos] = '\0';
#elif defined(__MACH__)
   if (!name)
      return;
   {
      size_t len_size = len;
      sysctlbyname("machdep.cpu.brand_string", name, &len_size, NULL, 0);
   }
#else
   if (!name)
      return;
   return;
#endif
}