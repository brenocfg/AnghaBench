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
 int FIXP ; 
 int H ; 
 int MY_PI ; 
 int W ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int* h_cos ; 
 int* h_sin ; 
 int int_sin (int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 char* tab_b ; 
 char* tab_g ; 
 char* tab_r ; 

__attribute__((used)) static int init_demo(const char *filename)
{
    int i, j;
    int h;
    int radian;
    char line[3 * W];

    FILE *input_file;

    input_file = fopen(filename, "rb");
    if (!input_file) {
        perror(filename);
        return 1;
    }

    if (fread(line, 1, 15, input_file) != 15)
        return 1;
    for (i = 0; i < H; i++) {
        if (fread(line, 1, 3 * W, input_file) != 3 * W)
            return 1;
        for (j = 0; j < W; j++) {
            tab_r[W * i + j] = line[3 * j    ];
            tab_g[W * i + j] = line[3 * j + 1];
            tab_b[W * i + j] = line[3 * j + 2];
        }
    }
    fclose(input_file);

    /* tables sin/cos */
    for (i = 0; i < 360; i++) {
        radian   = 2 * i * MY_PI / 360;
        h        = 2 * FIXP + int_sin(radian);
        h_cos[i] = h * int_sin(radian + MY_PI / 2) / 2 / FIXP;
        h_sin[i] = h * int_sin(radian)             / 2 / FIXP;
    }

    return 0;
}