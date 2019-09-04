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
struct TYPE_3__ {int***** ac_stats; scalar_t__ pict_type; int rl_table_index; int rl_chroma_table_index; scalar_t__ last_non_b_pict_type; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 int INT_MAX ; 
 int MAX_LEVEL ; 
 int MAX_RUN ; 
 int /*<<< orphan*/  memset (int*****,int /*<<< orphan*/ ,int) ; 
 int**** rl_length ; 

__attribute__((used)) static void find_best_tables(MpegEncContext * s)
{
    int i;
    int best        = 0, best_size        = INT_MAX;
    int chroma_best = 0, best_chroma_size = INT_MAX;

    for(i=0; i<3; i++){
        int level;
        int chroma_size=0;
        int size=0;

        if(i>0){// ;)
            size++;
            chroma_size++;
        }
        for(level=0; level<=MAX_LEVEL; level++){
            int run;
            for(run=0; run<=MAX_RUN; run++){
                int last;
                const int last_size= size + chroma_size;
                for(last=0; last<2; last++){
                    int inter_count       = s->ac_stats[0][0][level][run][last] + s->ac_stats[0][1][level][run][last];
                    int intra_luma_count  = s->ac_stats[1][0][level][run][last];
                    int intra_chroma_count= s->ac_stats[1][1][level][run][last];

                    if(s->pict_type==AV_PICTURE_TYPE_I){
                        size       += intra_luma_count  *rl_length[i  ][level][run][last];
                        chroma_size+= intra_chroma_count*rl_length[i+3][level][run][last];
                    }else{
                        size+=        intra_luma_count  *rl_length[i  ][level][run][last]
                                     +intra_chroma_count*rl_length[i+3][level][run][last]
                                     +inter_count       *rl_length[i+3][level][run][last];
                    }
                }
                if(last_size == size+chroma_size) break;
            }
        }
        if(size<best_size){
            best_size= size;
            best= i;
        }
        if(chroma_size<best_chroma_size){
            best_chroma_size= chroma_size;
            chroma_best= i;
        }
    }

    if(s->pict_type==AV_PICTURE_TYPE_P) chroma_best= best;

    memset(s->ac_stats, 0, sizeof(int)*(MAX_LEVEL+1)*(MAX_RUN+1)*2*2*2);

    s->rl_table_index       =        best;
    s->rl_chroma_table_index= chroma_best;

    if(s->pict_type != s->last_non_b_pict_type){
        s->rl_table_index= 2;
        if(s->pict_type==AV_PICTURE_TYPE_I)
            s->rl_chroma_table_index= 1;
        else
            s->rl_chroma_table_index= 2;
    }

}