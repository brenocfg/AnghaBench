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
struct TYPE_3__ {int n; char** data; } ;
typedef  TYPE_1__ moves ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char** calloc (int,int) ; 
 char* fgetgo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 void* realloc (char**,int) ; 

moves load_go_moves(char *filename)
{
    moves m;
    m.n = 128;
    m.data = calloc(128, sizeof(char*));
    FILE *fp = fopen(filename, "rb");
    int count = 0;
    char *line = 0;
    while ((line = fgetgo(fp))) {
        if (count >= m.n) {
            m.n *= 2;
            m.data = realloc(m.data, m.n*sizeof(char*));
        }
        m.data[count] = line;
        ++count;
    }
    printf("%d\n", count);
    m.n = count;
    m.data = realloc(m.data, count*sizeof(char*));
    return m;
}