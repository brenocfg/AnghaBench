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
struct global {int /*<<< orphan*/  skip; } ;
typedef  int png_uint_32 ;

/* Variables and functions */
 scalar_t__ CRITICAL (int) ; 
 int /*<<< orphan*/  SAFE_TO_COPY (int) ; 
 int /*<<< orphan*/  SKIP_ALL ; 
 int /*<<< orphan*/  SKIP_COLOR ; 
 int /*<<< orphan*/  SKIP_TRANSFORM ; 
 int /*<<< orphan*/  SKIP_UNSAFE ; 
 int /*<<< orphan*/  SKIP_UNUSED ; 
#define  png_bKGD 149 
#define  png_cHRM 148 
#define  png_fRAc 147 
#define  png_gAMA 146 
#define  png_gIFg 145 
#define  png_gIFt 144 
#define  png_gIFx 143 
#define  png_hIST 142 
#define  png_iCCP 141 
#define  png_iTXt 140 
#define  png_oFFs 139 
#define  png_pCAL 138 
#define  png_pHYs 137 
#define  png_sBIT 136 
#define  png_sCAL 135 
#define  png_sPLT 134 
#define  png_sRGB 133 
#define  png_sTER 132 
#define  png_tEXt 131 
#define  png_tIME 130 
#define  png_tRNS 129 
#define  png_zTXt 128 

__attribute__((used)) static int
skip_chunk_type(const struct global *global, png_uint_32 type)
   /* Return true if this chunk is to be skipped according to the --strip
    * option.  This code needs to recognize all known ancillary chunks in order
    * to handle the --strip=unsafe option.
    */
{
   /* Never strip critical chunks: */
   if (CRITICAL(type))
      return 0;

   switch (type)
   {
      /* Chunks that are treated as, effectively, critical because they affect
       * correct interpretation of the pixel values:
       */
      case png_tRNS: case png_sBIT:
         return 0;

      /* Chunks that specify gamma encoding which should therefore only be
       * removed the the user insists:
       */
      case png_gAMA: case png_sRGB:
         if (global->skip >= SKIP_ALL)
            return 1;
         return 0;

      /* Chunks that affect color interpretation - not used by libpng and rarely
       * used by applications, but technically still required for correct
       * interpretation of the image data:
       */
      case png_cHRM: case png_iCCP:
         if (global->skip >= SKIP_COLOR)
            return 1;
         return 0;

      /* Other chunks that are used by libpng in image transformations (as
       * opposed to known chunks that have get/set APIs but are not otherwise
       * used.)
       */
      case png_bKGD:
         if (global->skip >= SKIP_TRANSFORM)
            return 1;
         return 0;

      /* All other chunks that libpng knows about and affect neither image
       * interpretation nor libpng transforms - chunks that are effectively
       * unused by libpng even though libpng might recognize and store them.
       */
      case png_fRAc: case png_gIFg: case png_gIFt: case png_gIFx: case png_hIST:
      case png_iTXt: case png_oFFs: case png_pCAL: case png_pHYs: case png_sCAL:
      case png_sPLT: case png_sTER: case png_tEXt: case png_tIME: case png_zTXt:
         if (global->skip >= SKIP_UNUSED)
            return 1;
         return 0;

      /* Chunks that libpng does not know about (notice that this depends on the
       * list above including all known chunks!)  The decision here depends on
       * whether the safe-to-copy bit is set in the chunk type.
       */
      default:
         if (SAFE_TO_COPY(type))
         {
            if (global->skip >= SKIP_UNUSED) /* as above */
               return 1;
         }

         else if (global->skip >= SKIP_UNSAFE)
            return 1;

         return 0;
   }
}