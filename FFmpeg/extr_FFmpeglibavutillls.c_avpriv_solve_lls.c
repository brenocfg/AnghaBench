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
struct TYPE_3__ {double** covariance; int indep_count; double** coeff; double* variance; } ;
typedef  TYPE_1__ LLSModel ;

/* Variables and functions */
 int MAX_VARS_ALIGN ; 
 double sqrt (double) ; 

void avpriv_solve_lls(LLSModel *m, double threshold, unsigned short min_order)
{
    int i, j, k;
    double (*factor)[MAX_VARS_ALIGN] = (void *) &m->covariance[1][0];
    double (*covar) [MAX_VARS_ALIGN] = (void *) &m->covariance[1][1];
    double *covar_y                = m->covariance[0];
    int count                      = m->indep_count;

    for (i = 0; i < count; i++) {
        for (j = i; j < count; j++) {
            double sum = covar[i][j];

            for (k = 0; k <= i-1; k++)
                sum -= factor[i][k] * factor[j][k];

            if (i == j) {
                if (sum < threshold)
                    sum = 1.0;
                factor[i][i] = sqrt(sum);
            } else {
                factor[j][i] = sum / factor[i][i];
            }
        }
    }

    for (i = 0; i < count; i++) {
        double sum = covar_y[i + 1];

        for (k = 0; k <= i-1; k++)
            sum -= factor[i][k] * m->coeff[0][k];

        m->coeff[0][i] = sum / factor[i][i];
    }

    for (j = count - 1; j >= min_order; j--) {
        for (i = j; i >= 0; i--) {
            double sum = m->coeff[0][i];

            for (k = i + 1; k <= j; k++)
                sum -= factor[k][i] * m->coeff[j][k];

            m->coeff[j][i] = sum / factor[i][i];
        }

        m->variance[j] = covar_y[0];

        for (i = 0; i <= j; i++) {
            double sum = m->coeff[j][i] * covar[i][i] - 2 * covar_y[i + 1];

            for (k = 0; k < i; k++)
                sum += 2 * m->coeff[j][k] * covar[k][i];

            m->variance[j] += m->coeff[j][i] * sum;
        }
    }
}