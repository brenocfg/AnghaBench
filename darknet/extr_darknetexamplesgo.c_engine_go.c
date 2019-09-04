#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network ;
struct TYPE_11__ {int row; int col; double value; double mcts; } ;
typedef  TYPE_1__ move ;
struct TYPE_12__ {double* prior; double* mean; double result; int total_count; } ;
typedef  TYPE_2__ mcts_tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 float* calloc (int,int) ; 
 int /*<<< orphan*/  copy_cpu (int,float*,int,float*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgetl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flip_board (float*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  move_go (float*,int,int,int) ; 
 TYPE_2__* move_mcts (TYPE_2__*,int) ; 
 TYPE_1__ pick_move (TYPE_2__*,float,int) ; 
 TYPE_2__* ponder (TYPE_2__*,int /*<<< orphan*/ *,float*,float*,int,float) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  print_board (int /*<<< orphan*/ ,float*,int,int /*<<< orphan*/ ) ; 
 int print_game (float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__* run_mcts (TYPE_2__*,int /*<<< orphan*/ *,float*,float*,int,int,float,float) ; 
 int scanf (char*,...) ; 
 int /*<<< orphan*/  set_batch_network (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 double what_time_is_it_now () ; 

void engine_go(char *filename, char *weightfile, int mcts_iters, float secs, float temp, float cpuct, int anon, int resign)
{
    mcts_tree *root = 0;
    network *net = load_network(filename, weightfile, 0);
    set_batch_network(net, 1);
    srand(time(0));
    float *board = calloc(19*19*3, sizeof(float));
    flip_board(board);
    float *one = calloc(19*19*3, sizeof(float));
    float *two = calloc(19*19*3, sizeof(float));
    int ponder_player = 0;
    int passed = 0;
    int move_num = 0;
    int main_time = 0;
    int byo_yomi_time = 0;
    int byo_yomi_stones = 0;
    int black_time_left = 0;
    int black_stones_left = 0;
    int white_time_left = 0;
    int white_stones_left = 0;
    float orig_time = secs;
    int old_ponder = 0;
    while(1){
        if(ponder_player){
            root = ponder(root, net, board, two, ponder_player, cpuct);
        }
        old_ponder = ponder_player;
        ponder_player = 0;
        char buff[256];
        int id = 0;
        int has_id = (scanf("%d", &id) == 1);
        scanf("%s", buff);
        if (feof(stdin)) break;
        fprintf(stderr, "%s\n", buff);
        char ids[256];
        sprintf(ids, "%d", id);
        //fprintf(stderr, "%s\n", buff);
        if (!has_id) ids[0] = 0;
        if (!strcmp(buff, "protocol_version")){
            printf("=%s 2\n\n", ids);
        } else if (!strcmp(buff, "name")){
            if(anon){
                printf("=%s The Fool!\n\n", ids);
            }else{
                printf("=%s DarkGo\n\n", ids);
            }
        } else if (!strcmp(buff, "time_settings")){
            ponder_player = old_ponder;
            scanf("%d %d %d", &main_time, &byo_yomi_time, &byo_yomi_stones);
            printf("=%s \n\n", ids);
        } else if (!strcmp(buff, "time_left")){
            ponder_player = old_ponder;
            char color[256];
            int time = 0, stones = 0;
            scanf("%s %d %d", color, &time, &stones);
            if (color[0] == 'b' || color[0] == 'B'){
                black_time_left = time;
                black_stones_left = stones;
            } else {
                white_time_left = time;
                white_stones_left = stones;
            }
            printf("=%s \n\n", ids);
        } else if (!strcmp(buff, "version")){
            if(anon){
                printf("=%s :-DDDD\n\n", ids);
            }else {
                printf("=%s 1.0. Want more DarkGo? You can find me on OGS, unlimited games, no waiting! https://online-go.com/user/view/434218\n\n", ids);
            }
        } else if (!strcmp(buff, "known_command")){
            char comm[256];
            scanf("%s", comm);
            int known = (!strcmp(comm, "protocol_version") || 
                    !strcmp(comm, "name") || 
                    !strcmp(comm, "version") || 
                    !strcmp(comm, "known_command") || 
                    !strcmp(comm, "list_commands") || 
                    !strcmp(comm, "quit") || 
                    !strcmp(comm, "boardsize") || 
                    !strcmp(comm, "clear_board") || 
                    !strcmp(comm, "komi") || 
                    !strcmp(comm, "final_status_list") || 
                    !strcmp(comm, "play") || 
                    !strcmp(comm, "genmove_white") || 
                    !strcmp(comm, "genmove_black") || 
                    !strcmp(comm, "fixed_handicap") || 
                    !strcmp(comm, "genmove"));
            if(known) printf("=%s true\n\n", ids);
            else printf("=%s false\n\n", ids);
        } else if (!strcmp(buff, "list_commands")){
            printf("=%s protocol_version\nshowboard\nname\nversion\nknown_command\nlist_commands\nquit\nboardsize\nclear_board\nkomi\nplay\ngenmove_black\ngenmove_white\ngenmove\nfinal_status_list\nfixed_handicap\n\n", ids);
        } else if (!strcmp(buff, "quit")){
            break;
        } else if (!strcmp(buff, "boardsize")){
            int boardsize = 0;
            scanf("%d", &boardsize);
            //fprintf(stderr, "%d\n", boardsize);
            if(boardsize != 19){
                printf("?%s unacceptable size\n\n", ids);
            } else {
                root = move_mcts(root, -1);
                memset(board, 0, 3*19*19*sizeof(float));
                flip_board(board);
                move_num = 0;
                printf("=%s \n\n", ids);
            }
        } else if (!strcmp(buff, "fixed_handicap")){
            int handicap = 0;
            scanf("%d", &handicap);
            int indexes[] = {72, 288, 300, 60, 180, 174, 186, 66, 294};
            int i;
            for(i = 0; i < handicap; ++i){
                board[indexes[i]] = 1;   
                ++move_num;
            }
            root = move_mcts(root, -1);
        } else if (!strcmp(buff, "clear_board")){
            passed = 0;
            memset(board, 0, 3*19*19*sizeof(float));
            flip_board(board);
            move_num = 0;
            root = move_mcts(root, -1);
            printf("=%s \n\n", ids);
        } else if (!strcmp(buff, "komi")){
            float komi = 0;
            scanf("%f", &komi);
            printf("=%s \n\n", ids);
        } else if (!strcmp(buff, "showboard")){
            printf("=%s \n", ids);
            print_board(stdout, board, 1, 0);
            printf("\n");
        } else if (!strcmp(buff, "play") || !strcmp(buff, "black") || !strcmp(buff, "white")){
            ++move_num;
            char color[256];
            if(!strcmp(buff, "play"))
            {
                scanf("%s ", color);
            } else {
                scanf(" ");
                color[0] = buff[0];
            }
            char c;
            int r;
            int count = scanf("%c%d", &c, &r);
            int player = (color[0] == 'b' || color[0] == 'B') ? 1 : -1;
            if((c == 'p' || c == 'P') && count < 2) {
                passed = 1;
                printf("=%s \n\n", ids);
                char *line = fgetl(stdin);
                free(line);
                fflush(stdout);
                fflush(stderr);
                root = move_mcts(root, 19*19);
                continue;
            } else {
                passed = 0;
            }
            if(c >= 'A' && c <= 'Z') c = c - 'A';
            if(c >= 'a' && c <= 'z') c = c - 'a';
            if(c >= 8) --c;
            r = 19 - r;
            fprintf(stderr, "move: %d %d\n", r, c);

            float *swap = two;
            two = one;
            one = swap;
            move_go(board, player, r, c);
            copy_cpu(19*19*3, board, 1, one, 1);
            if(root) fprintf(stderr, "Prior: %f\n", root->prior[r*19 + c]);
            if(root) fprintf(stderr, "Mean: %f\n", root->mean[r*19 + c]);
            if(root) fprintf(stderr, "Result: %f\n", root->result);
            root = move_mcts(root, r*19 + c);
            if(root) fprintf(stderr, "Visited: %d\n", root->total_count);
            else fprintf(stderr, "NOT VISITED\n");

            printf("=%s \n\n", ids);
            //print_board(stderr, board, 1, 0);
        } else if (!strcmp(buff, "genmove") || !strcmp(buff, "genmove_black") || !strcmp(buff, "genmove_white")){
            ++move_num;
            int player = 0;
            if(!strcmp(buff, "genmove")){
                char color[256];
                scanf("%s", color);
                player = (color[0] == 'b' || color[0] == 'B') ? 1 : -1;
            } else if (!strcmp(buff, "genmove_black")){
                player = 1;
            } else {
                player = -1;
            }
            if(player > 0){
                if(black_time_left <= 30) secs = 2.5;
                else secs = orig_time;
            } else {
                if(white_time_left <= 30) secs = 2.5;
                else secs = orig_time;
            }
            ponder_player = -player;

            //tree = generate_move(net, player, board, multi, .1, two, 1);
            double t = what_time_is_it_now();
            root = run_mcts(root, net, board, two, player, mcts_iters, cpuct, secs);
            fprintf(stderr, "%f Seconds\n", what_time_is_it_now() - t);
            move m = pick_move(root, temp, player);
            root = move_mcts(root, m.row*19 + m.col);


            if(move_num > resign && m.value < .1 && m.mcts < .1){
                printf("=%s resign\n\n", ids);
            } else if(m.row == 19){
                printf("=%s pass\n\n", ids);
                passed = 0;
            } else {
                int row = m.row;
                int col = m.col;

                float *swap = two;
                two = one;
                one = swap;

                move_go(board, player, row, col);
                copy_cpu(19*19*3, board, 1, one, 1);
                row = 19 - row;
                if (col >= 8) ++col;
                printf("=%s %c%d\n\n", ids, 'A' + col, row);
            }

        } else if (!strcmp(buff, "p")){
            //print_board(board, 1, 0);
        } else if (!strcmp(buff, "final_status_list")){
            char type[256];
            scanf("%s", type);
            fprintf(stderr, "final_status\n");
            char *line = fgetl(stdin);
            free(line);
            if(type[0] == 'd' || type[0] == 'D'){
                int i;
                FILE *f = fopen("game.txt", "w");
                int count = print_game(board, f);
                fprintf(f, "%s final_status_list dead\n", ids);
                fclose(f);
                FILE *p = popen("./gnugo --mode gtp < game.txt", "r");
                for(i = 0; i < count; ++i){
                    free(fgetl(p));
                    free(fgetl(p));
                }
                char *l = 0;
                while((l = fgetl(p))){
                    printf("%s\n", l);
                    free(l);
                }
            } else {
                printf("?%s unknown command\n\n", ids);
            }
        } else if (!strcmp(buff, "kgs-genmove_cleanup")){
            char type[256];
            scanf("%s", type);
            fprintf(stderr, "kgs-genmove_cleanup\n");
            char *line = fgetl(stdin);
            free(line);
            int i;
            FILE *f = fopen("game.txt", "w");
            int count = print_game(board, f);
            fprintf(f, "%s kgs-genmove_cleanup %s\n", ids, type);
            fclose(f);
            FILE *p = popen("./gnugo --mode gtp < game.txt", "r");
            for(i = 0; i < count; ++i){
                free(fgetl(p));
                free(fgetl(p));
            }
            char *l = 0;
            while((l = fgetl(p))){
                printf("%s\n", l);
                free(l);
            }
        } else {
            char *line = fgetl(stdin);
            free(line);
            printf("?%s unknown command\n\n", ids);
        }
        fflush(stdout);
        fflush(stderr);
    }
    printf("%d %d %d\n",passed, black_stones_left, white_stones_left);
}