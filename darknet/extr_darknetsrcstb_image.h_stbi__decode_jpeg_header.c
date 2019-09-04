#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int app14_color_transform; int marker; int /*<<< orphan*/  progressive; int /*<<< orphan*/  s; scalar_t__ jfif; } ;
typedef  TYPE_1__ stbi__jpeg ;

/* Variables and functions */
 int STBI__MARKER_none ; 
 int STBI__SCAN_type ; 
 int /*<<< orphan*/  stbi__SOF (int) ; 
 int /*<<< orphan*/  stbi__SOF_progressive (int) ; 
 int /*<<< orphan*/  stbi__SOI (int) ; 
 scalar_t__ stbi__at_eof (int /*<<< orphan*/ ) ; 
 int stbi__err (char*,char*) ; 
 int stbi__get_marker (TYPE_1__*) ; 
 int /*<<< orphan*/  stbi__process_frame_header (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stbi__process_marker (TYPE_1__*,int) ; 

__attribute__((used)) static int stbi__decode_jpeg_header(stbi__jpeg *z, int scan)
{
   int m;
   z->jfif = 0;
   z->app14_color_transform = -1; // valid values are 0,1,2
   z->marker = STBI__MARKER_none; // initialize cached marker to empty
   m = stbi__get_marker(z);
   if (!stbi__SOI(m)) return stbi__err("no SOI","Corrupt JPEG");
   if (scan == STBI__SCAN_type) return 1;
   m = stbi__get_marker(z);
   while (!stbi__SOF(m)) {
      if (!stbi__process_marker(z,m)) return 0;
      m = stbi__get_marker(z);
      while (m == STBI__MARKER_none) {
         // some files have extra padding after their blocks, so ok, we'll scan
         if (stbi__at_eof(z->s)) return stbi__err("no SOF", "Corrupt JPEG");
         m = stbi__get_marker(z);
      }
   }
   z->progressive = stbi__SOF_progressive(m);
   if (!stbi__process_frame_header(z, scan)) return 0;
   return 1;
}