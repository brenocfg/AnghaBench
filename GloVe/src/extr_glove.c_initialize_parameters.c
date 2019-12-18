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
typedef  double real ;

/* Variables and functions */
 scalar_t__ RAND_MAX ; 
 double* W ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 double* gradsq ; 
 long long posix_memalign (void**,int,int) ; 
 double rand () ; 
 int /*<<< orphan*/  stderr ; 
 int vector_size ; 
 int vocab_size ; 

void initialize_parameters() {
    long long a, b;
    vector_size++; // Temporarily increment to allocate space for bias

    /* Allocate space for word vectors and context word vectors, and correspodning gradsq */
    a = posix_memalign((void **)&W, 128, 2 * vocab_size * vector_size * sizeof(real)); // Might perform better than malloc
    if (W == NULL) {
        fprintf(stderr, "Error allocating memory for W\n");
        exit(1);
    }
    a = posix_memalign((void **)&gradsq, 128, 2 * vocab_size * vector_size * sizeof(real)); // Might perform better than malloc
    if (gradsq == NULL) {
        fprintf(stderr, "Error allocating memory for gradsq\n");
        exit(1);
    }
    for (b = 0; b < vector_size; b++) {
        for (a = 0; a < 2 * vocab_size; a++) {
            W[a * vector_size + b] = (rand() / (real)RAND_MAX - 0.5) / vector_size;
        }
    }
    for (b = 0; b < vector_size; b++) {
        for (a = 0; a < 2 * vocab_size; a++) {
            gradsq[a * vector_size + b] = 1.0; // So initial value of eta is equal to initial learning rate
        }
    }
    vector_size--;
}