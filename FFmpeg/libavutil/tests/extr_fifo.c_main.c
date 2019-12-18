#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  j ;
struct TYPE_13__ {int rndx; int wndx; } ;
typedef  TYPE_1__ AVFifoBuffer ;

/* Variables and functions */
 TYPE_1__* av_fifo_alloc (int) ; 
 int /*<<< orphan*/  av_fifo_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_fifo_generic_peek (TYPE_1__*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_peek_at (TYPE_1__*,int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_read (TYPE_1__*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_write (TYPE_1__*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_grow (TYPE_1__*,int) ; 
 scalar_t__ av_fifo_peek2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_fifo_reset (TYPE_1__*) ; 
 int av_fifo_size (TYPE_1__*) ; 
 int av_fifo_space (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
    /* create a FIFO buffer */
    AVFifoBuffer *fifo = av_fifo_alloc(13 * sizeof(int));
    int i, j, n, *p;

    /* fill data */
    for (i = 0; av_fifo_space(fifo) >= sizeof(int); i++)
        av_fifo_generic_write(fifo, &i, sizeof(int), NULL);

    /* peek at FIFO */
    n = av_fifo_size(fifo) / sizeof(int);
    for (i = -n + 1; i < n; i++) {
        int *v = (int *)av_fifo_peek2(fifo, i * sizeof(int));
        printf("%d: %d\n", i, *v);
    }
    printf("\n");

    /* peek_at at FIFO */
    n = av_fifo_size(fifo) / sizeof(int);
    for (i = 0; i < n; i++) {
        av_fifo_generic_peek_at(fifo, &j, i * sizeof(int), sizeof(j), NULL);
        printf("%d: %d\n", i, j);
    }
    printf("\n");

    /* generic peek at FIFO */

    n = av_fifo_size(fifo);
    p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "failed to allocate memory.\n");
        exit(1);
    }

    (void) av_fifo_generic_peek(fifo, p, n, NULL);

    /* read data at p */
    n /= sizeof(int);
    for(i = 0; i < n; ++i)
        printf("%d: %d\n", i, p[i]);

    putchar('\n');

    /* read data */
    for (i = 0; av_fifo_size(fifo) >= sizeof(int); i++) {
        av_fifo_generic_read(fifo, &j, sizeof(int), NULL);
        printf("%d ", j);
    }
    printf("\n");

    /* test *ndx overflow */
    av_fifo_reset(fifo);
    fifo->rndx = fifo->wndx = ~(uint32_t)0 - 5;

    /* fill data */
    for (i = 0; av_fifo_space(fifo) >= sizeof(int); i++)
        av_fifo_generic_write(fifo, &i, sizeof(int), NULL);

    /* peek_at at FIFO */
    n = av_fifo_size(fifo) / sizeof(int);
    for (i = 0; i < n; i++) {
        av_fifo_generic_peek_at(fifo, &j, i * sizeof(int), sizeof(j), NULL);
        printf("%d: %d\n", i, j);
    }
    putchar('\n');

    /* test fifo_grow */
    (void) av_fifo_grow(fifo, 15 * sizeof(int));

    /* fill data */
    n = av_fifo_size(fifo) / sizeof(int);
    for (i = n; av_fifo_space(fifo) >= sizeof(int); ++i)
        av_fifo_generic_write(fifo, &i, sizeof(int), NULL);

    /* peek_at at FIFO */
    n = av_fifo_size(fifo) / sizeof(int);
    for (i = 0; i < n; i++) {
        av_fifo_generic_peek_at(fifo, &j, i * sizeof(int), sizeof(j), NULL);
        printf("%d: %d\n", i, j);
    }

    av_fifo_free(fifo);
    free(p);

    return 0;
}