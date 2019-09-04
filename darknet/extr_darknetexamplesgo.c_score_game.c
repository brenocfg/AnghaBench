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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgetl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int print_game (float*,int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,char*,float*) ; 
 int /*<<< orphan*/  stderr ; 

float score_game(float *board)
{
    int i;
    FILE *f = fopen("game.txt", "w");
    int count = print_game(board, f);
    fprintf(f, "final_score\n");
    fclose(f);
    FILE *p = popen("./gnugo --mode gtp < game.txt", "r");
    for(i = 0; i < count; ++i){
        free(fgetl(p));
        free(fgetl(p));
    }
    char *l = 0;
    float score = 0;
    char player = 0;
    while((l = fgetl(p))){
        fprintf(stderr, "%s  \t", l);
        int n = sscanf(l, "= %c+%f", &player, &score);
        free(l);
        if (n == 2) break;
    }
    if(player == 'W') score = -score;
    pclose(p);
    return score;
}