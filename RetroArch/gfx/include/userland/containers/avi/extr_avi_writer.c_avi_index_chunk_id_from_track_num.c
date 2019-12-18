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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  track_num_buf ;
typedef  scalar_t__ VC_CONTAINER_FOURCC_T ;

/* Variables and functions */
 scalar_t__ VC_FOURCC (char,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void avi_index_chunk_id_from_track_num(VC_CONTAINER_FOURCC_T *p_chunk_id,
   unsigned int track_num )
{
   VC_CONTAINER_FOURCC_T chunk_id = 0;
   char track_num_buf[3];

   chunk_id = VC_FOURCC('i','x','0','0');

   snprintf(track_num_buf, sizeof(track_num_buf), "%02d", track_num);
   memcpy(((uint8_t*)&chunk_id) + 2, track_num_buf, 2);

   *p_chunk_id = chunk_id;
}