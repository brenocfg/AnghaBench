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
struct uwb_rsv_col_set_info {int start_col; int interval; int safe_mas_per_col; int unsafe_mas_per_col; } ;
struct uwb_rsv_col_info {int max_avail_safe; int max_avail_unsafe; int* highest_mas; struct uwb_rsv_col_set_info csi; } ;
struct uwb_rsv_alloc_info {int safe_allocated_mases; int unsafe_allocated_mases; int total_allocated_mases; int interval; struct uwb_rsv_col_info* ci; } ;

/* Variables and functions */
 int UWB_MAS_PER_ZONE ; 
 int UWB_NUM_ZONES ; 
 int UWB_RSV_ALLOC_FOUND ; 
 int UWB_RSV_ALLOC_NOT_FOUND ; 

__attribute__((used)) static int uwb_rsv_find_best_column_set(struct uwb_rsv_alloc_info *ai, int interval, 
					int num_safe_mas, int num_unsafe_mas)
{
	struct uwb_rsv_col_info *ci = ai->ci;
	struct uwb_rsv_col_set_info *csi = &ci->csi;
	struct uwb_rsv_col_set_info tmp_csi;
	int deep, set, col, start_col_deep, col_start_set;
	int start_col, max_mas_in_set, lowest_max_mas_in_deep;
	int n_mas;
	int found = UWB_RSV_ALLOC_NOT_FOUND; 

	tmp_csi.start_col = 0;
	start_col_deep = interval;
	n_mas = num_unsafe_mas + num_safe_mas;

	for (deep = 0; ((interval >> deep) & 0x1) == 0; deep++) {
		start_col_deep /= 2;
		col_start_set = 0;
		lowest_max_mas_in_deep = UWB_MAS_PER_ZONE;

		for (set = 1; set <= (1 << deep); set++) {
			max_mas_in_set = 0;
			start_col = start_col_deep + col_start_set;
			for (col = start_col; col < UWB_NUM_ZONES; col += interval) {
                
				if (ci[col].max_avail_safe >= num_safe_mas &&
				    ci[col].max_avail_unsafe >= n_mas) {
					if (ci[col].highest_mas[n_mas] > max_mas_in_set)
						max_mas_in_set = ci[col].highest_mas[n_mas];
				} else {
					max_mas_in_set = 0;
					break;
				}
			}
			if ((lowest_max_mas_in_deep > max_mas_in_set) && max_mas_in_set) {
				lowest_max_mas_in_deep = max_mas_in_set;

				tmp_csi.start_col = start_col;
			}
			col_start_set += (interval >> deep);
		}

		if (lowest_max_mas_in_deep < 8) {
			csi->start_col = tmp_csi.start_col;
			found = UWB_RSV_ALLOC_FOUND;
			break;
		} else if ((lowest_max_mas_in_deep > 8) && 
			   (lowest_max_mas_in_deep != UWB_MAS_PER_ZONE) &&
			   (found == UWB_RSV_ALLOC_NOT_FOUND)) {
			csi->start_col = tmp_csi.start_col;
			found = UWB_RSV_ALLOC_FOUND;
		}
	}

	if (found == UWB_RSV_ALLOC_FOUND) {
		csi->interval = interval;
		csi->safe_mas_per_col = num_safe_mas;
		csi->unsafe_mas_per_col = num_unsafe_mas;

		ai->safe_allocated_mases = (UWB_NUM_ZONES / interval) * num_safe_mas;
		ai->unsafe_allocated_mases = (UWB_NUM_ZONES / interval) * num_unsafe_mas;
		ai->total_allocated_mases = ai->safe_allocated_mases + ai->unsafe_allocated_mases;
		ai->interval = interval;		
	}
	return found;
}