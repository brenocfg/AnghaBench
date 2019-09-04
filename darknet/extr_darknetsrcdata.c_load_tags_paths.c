#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int** vals; } ;
typedef  TYPE_1__ matrix ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_replace (char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 TYPE_1__ make_matrix (int,int) ; 

matrix load_tags_paths(char **paths, int n, int k)
{
    matrix y = make_matrix(n, k);
    int i;
    //int count = 0;
    for(i = 0; i < n; ++i){
        char label[4096];
        find_replace(paths[i], "images", "labels", label);
        find_replace(label, ".jpg", ".txt", label);
        FILE *file = fopen(label, "r");
        if (!file) continue;
        //++count;
        int tag;
        while(fscanf(file, "%d", &tag) == 1){
            if(tag < k){
                y.vals[i][tag] = 1;
            }
        }
        fclose(file);
    }
    //printf("%d/%d\n", count, n);
    return y;
}