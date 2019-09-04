#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ stbi__uint32 ;
struct TYPE_14__ {scalar_t__ progressive; TYPE_8__* s; void* marker; scalar_t__ restart_interval; TYPE_1__* img_comp; } ;
typedef  TYPE_2__ stbi__jpeg ;
struct TYPE_15__ {scalar_t__ img_y; } ;
struct TYPE_13__ {int /*<<< orphan*/ * raw_coeff; int /*<<< orphan*/ * raw_data; } ;

/* Variables and functions */
 void* STBI__MARKER_none ; 
 int /*<<< orphan*/  STBI__SCAN_load ; 
 scalar_t__ stbi__DNL (int) ; 
 int /*<<< orphan*/  stbi__EOI (int) ; 
 scalar_t__ stbi__SOS (int) ; 
 int /*<<< orphan*/  stbi__at_eof (TYPE_8__*) ; 
 int /*<<< orphan*/  stbi__decode_jpeg_header (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int stbi__err (char*,char*) ; 
 void* stbi__get16be (TYPE_8__*) ; 
 void* stbi__get8 (TYPE_8__*) ; 
 int stbi__get_marker (TYPE_2__*) ; 
 int /*<<< orphan*/  stbi__jpeg_finish (TYPE_2__*) ; 
 int /*<<< orphan*/  stbi__parse_entropy_coded_data (TYPE_2__*) ; 
 int /*<<< orphan*/  stbi__process_marker (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stbi__process_scan_header (TYPE_2__*) ; 

__attribute__((used)) static int stbi__decode_jpeg_image(stbi__jpeg *j)
{
   int m;
   for (m = 0; m < 4; m++) {
      j->img_comp[m].raw_data = NULL;
      j->img_comp[m].raw_coeff = NULL;
   }
   j->restart_interval = 0;
   if (!stbi__decode_jpeg_header(j, STBI__SCAN_load)) return 0;
   m = stbi__get_marker(j);
   while (!stbi__EOI(m)) {
      if (stbi__SOS(m)) {
         if (!stbi__process_scan_header(j)) return 0;
         if (!stbi__parse_entropy_coded_data(j)) return 0;
         if (j->marker == STBI__MARKER_none ) {
            // handle 0s at the end of image data from IP Kamera 9060
            while (!stbi__at_eof(j->s)) {
               int x = stbi__get8(j->s);
               if (x == 255) {
                  j->marker = stbi__get8(j->s);
                  break;
               }
            }
            // if we reach eof without hitting a marker, stbi__get_marker() below will fail and we'll eventually return 0
         }
      } else if (stbi__DNL(m)) {
         int Ld = stbi__get16be(j->s);
         stbi__uint32 NL = stbi__get16be(j->s);
         if (Ld != 4) return stbi__err("bad DNL len", "Corrupt JPEG");
         if (NL != j->s->img_y) return stbi__err("bad DNL height", "Corrupt JPEG");
      } else {
         if (!stbi__process_marker(j, m)) return 0;
      }
      m = stbi__get_marker(j);
   }
   if (j->progressive)
      stbi__jpeg_finish(j);
   return 1;
}