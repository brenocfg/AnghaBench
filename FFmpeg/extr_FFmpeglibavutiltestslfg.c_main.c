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
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int** Z_TABLE ; 
 int /*<<< orphan*/  av_bmg_get (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  av_freep (double**) ; 
 scalar_t__ av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 
 double* av_malloc_array (double,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 double inv_cdf (int) ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double,...) ; 
 double sqrt (double) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
    int x = 0;
    int i, j;
    AVLFG state;
    av_lfg_init(&state, 0xdeadbeef);
    for (j = 0; j < 10000; j++) {
        for (i = 0; i < 624; i++) {
            //av_log(NULL, AV_LOG_ERROR, "%X\n", av_lfg_get(&state));
            x += av_lfg_get(&state);
        }
    }
    av_log(NULL, AV_LOG_ERROR, "final value:%X\n", x);

    /* BMG usage example */
    {
        double mean   = 1000;
        double stddev = 53;
        double samp_mean = 0.0, samp_stddev = 0.0, QH = 0;
        double Z, p_value = -1, tot_samp = 1000;
        double *PRN_arr = av_malloc_array(tot_samp, sizeof(double));

        if (!PRN_arr) {
            fprintf(stderr, "failed to allocate memory!\n");
            return 1;
        }

        av_lfg_init(&state, 42);
        for (i = 0; i < tot_samp; i += 2) {
            double bmg_out[2];
            av_bmg_get(&state, bmg_out);
            PRN_arr[i  ] = bmg_out[0] * stddev + mean;
            PRN_arr[i+1] = bmg_out[1] * stddev + mean;
            samp_mean   += PRN_arr[i] + PRN_arr[i+1];
            samp_stddev += PRN_arr[i] * PRN_arr[i] + PRN_arr[i+1] * PRN_arr[i+1];
            printf("PRN%d : %f\n"
                   "PRN%d : %f\n",
                   i, PRN_arr[i], i+1, PRN_arr[i+1]);
        }
        samp_mean /= tot_samp;
        samp_stddev /= (tot_samp - 1);
        samp_stddev -= (tot_samp * 1.0 / (tot_samp - 1))*samp_mean*samp_mean;
        samp_stddev = sqrt(samp_stddev);
        Z = (mean - samp_mean) / (stddev / sqrt(tot_samp));
        {
            int x, y, a, b, flag = 0;

            if (Z < 0.0) {
                flag = !flag;
                Z = Z * -1.0;
            }

            a = (int)(Z * 100);
            b = ((int)Z * 100);
            x = Z * 10;
            y = (b > 0) ? a % b : a;
            y = y % 10;
            if (x > 30 || y > 9) {
                av_log(NULL, AV_LOG_INFO, "error: out of bounds! tried to access"
                                          "Z_TABLE[%d][%d]\n", x, y);
                goto SKIP;
            }
            p_value = flag ? 1 - Z_TABLE[x][y] : Z_TABLE[x][y];
        }

SKIP:   for (i = 0; i < tot_samp; ++i) {

            if ( i < (tot_samp - 1)) {
                double H_diff;
                H_diff  = inv_cdf((i + 2.0 - (3.0/8.0)) / (tot_samp + (1.0/4.0)));
                H_diff -= inv_cdf((i + 1.0 - (3.0/8.0)) / (tot_samp + (1.0/4.0)));

                QH     += ((PRN_arr[i + 1] - PRN_arr[i]) / H_diff);
            }
        }
        QH = 1.0 - QH / ((tot_samp - 1.0) * samp_stddev);

        printf("sample mean  : %f\n"
               "true mean    : %f\n"
               "sample stddev: %f\n"
               "true stddev  : %f\n"
               "z-score      : %f\n"
               "p-value      : %f\n"
               "QH[normality]: %f\n",
               samp_mean, mean, samp_stddev, stddev, Z, p_value, QH);

        av_freep(&PRN_arr);
    }
    return 0;
}