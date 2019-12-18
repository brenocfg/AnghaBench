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
typedef  int uint64_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static bool update_cand(int64_t *cand_index, int64_t *last_index,
                        uint64_t *largest, char *last_file, uint64_t *offset,
                        uint64_t *size, char *track_path, uint64_t max_len)
{
   if (*cand_index != -1)
   {
      if ((uint64_t)(*last_index - *cand_index) > *largest)
      {
         *largest    = *last_index - *cand_index;
         strlcpy(track_path, last_file, (size_t)max_len);
         *offset     = *cand_index;
         *size       = *largest;
         *cand_index = -1;
         return true;
      }
      *cand_index = -1;
   }
   return false;
}