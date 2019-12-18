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
typedef  int UInt32 ;
typedef  int /*<<< orphan*/  UInt16 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int Int32 ;

/* Variables and functions */
 scalar_t__ True ; 
 int* incs ; 
 scalar_t__ mainGtU (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static
void mainSimpleSort ( UInt32* ptr,
                      UChar*  block,
                      UInt16* quadrant,
                      Int32   nblock,
                      Int32   lo, 
                      Int32   hi, 
                      Int32   d,
                      Int32*  budget )
{
   Int32 i, j, h, bigN, hp;
   UInt32 v;

   bigN = hi - lo + 1;
   if (bigN < 2) return;

   hp = 0;
   while (incs[hp] < bigN) hp++;
   hp--;

   for (; hp >= 0; hp--) {
      h = incs[hp];

      i = lo + h;
      while (True) {

         /*-- copy 1 --*/
         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU ( 
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget 
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;

         /*-- copy 2 --*/
         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU ( 
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget 
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;

         /*-- copy 3 --*/
         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU ( 
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget 
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;

         if (*budget < 0) return;
      }
   }
}