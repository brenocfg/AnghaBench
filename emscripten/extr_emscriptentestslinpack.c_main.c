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
typedef  int REAL ;

/* Variables and functions */
 int NTIMES ; 
 int /*<<< orphan*/  ONE ; 
 char* PREC ; 
 char* ROLLING ; 
 double** atime ; 
 int /*<<< orphan*/  dgefa (int*,int,int,int*,int*) ; 
 int /*<<< orphan*/  dgesl (int*,int,int,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmxpy (int,int*,int,int,int*,int*) ; 
 int /*<<< orphan*/  end_time () ; 
 int epslon (int /*<<< orphan*/ ) ; 
 int fabs (double) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  matgen (int*,int,int,int*,int*) ; 
 int /*<<< orphan*/  opt ; 
 char* options ; 
 int /*<<< orphan*/  print_time (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int runSecs ; 
 int secs ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  start_time () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int main (int argc, char *argv[])
{
        static REAL aa[200*200],a[200*201],b[200],x[200];       
        REAL cray,ops,total,norma,normx;
        REAL resid,residn,eps,tm2,epsn,x1,x2;
        REAL mflops;
        static int ipvt[200],n,i,j,ntimes,info,lda,ldaa;
        int endit, pass, loop;
        REAL overhead1, overhead2, time2;
        REAL max1, max2;
        char was[5][20];
        char expect[5][20];
        char title[5][20];
        int errors;
        
        int arg = argc > 1 ? argv[1][0] - '0' : 3;
        if (arg == 0) return 0;
 
        printf("\n");
         
        printf("##########################################\n"); 


    
        lda = 201;
        ldaa = 200;
        cray = .056; 
        n = 100;

        fprintf(stdout, "%s ", ROLLING);
        fprintf(stdout, "%s ", PREC);
        fprintf(stdout,"Precision Linpack Benchmark - PC Version in 'C/C++'\n\n");

        fprintf(stdout,"Optimisation %s\n\n",options);

        ops = (2.0e0*(n*n*n))/3.0 + 2.0*(n*n);

        matgen(a,lda,n,b,&norma);
        start_time();
        dgefa(a,lda,n,ipvt,&info);
        end_time();
        atime[0][0] = secs;
        start_time();
        dgesl(a,lda,n,ipvt,b,0);
        end_time();
        atime[1][0] = secs;
        total = atime[0][0] + atime[1][0];

/*     compute a residual to verify results.  */ 

        for (i = 0; i < n; i++) {
                x[i] = b[i];
        }
        matgen(a,lda,n,b,&norma);
        for (i = 0; i < n; i++) {
                b[i] = -b[i];
        }
        dmxpy(n,b,n,lda,x,a);
        resid = 0.0;
        normx = 0.0;
        for (i = 0; i < n; i++) {
                resid = (resid > fabs((double)b[i])) 
                        ? resid : fabs((double)b[i]);
                normx = (normx > fabs((double)x[i])) 
                        ? normx : fabs((double)x[i]);
        }
        eps = epslon(ONE);
        residn = resid/( n*norma*normx*eps );
        epsn = eps;
        x1 = x[0] - 1;
        x2 = x[n-1] - 1;
        
        printf("norm resid      resid           machep");
        printf("         x[0]-1          x[n-1]-1\n");
        printf("%6.1f %17.8e%17.8e%17.8e%17.8e\n\n",
               (double)residn, (double)resid, (double)epsn, 
               (double)x1, (double)x2);

        printf("Times are reported for matrices of order        %5d\n",n);
        printf("1 pass times for array with leading dimension of%5d\n\n",lda);
        printf("      dgefa      dgesl      total     Mflops       unit");
        printf("      ratio\n");

        atime[2][0] = total;
        if (total > 0.0)
        {
            atime[3][0] = ops/(1.0e6*total);
            atime[4][0] = 2.0/atime[3][0];
        }
        else
        {
            atime[3][0] = 0.0;
            atime[4][0] = 0.0;
        }
        atime[5][0] = total/cray;
       
        print_time(0);

/************************************************************************
 *       Calculate overhead of executing matgen procedure              *
 ************************************************************************/
       
        printf("\nCalculating matgen overhead\n");
        pass = -20;
        loop = NTIMES;
        do
        {
            start_time();
            pass = pass + 1;        
            for ( i = 0 ; i < loop ; i++)
            {
                 matgen(a,lda,n,b,&norma);
            }
            end_time();
            overhead1 = secs;
            printf("%10d times %6.2f seconds\n", loop, overhead1);
            if (overhead1 > runSecs)
            {
                pass = 0;
            }
            if (pass < 0)
            {
                if (overhead1 < 0.1)
                {
                    loop = loop * 10;
                }
                else
                {
                    loop = loop * 2;
                }
            }
        }
        while (pass < 0);
        
        overhead1 = overhead1 / (double)loop;

        printf("Overhead for 1 matgen %12.5f seconds\n\n", overhead1);

/************************************************************************
 *           Calculate matgen/dgefa passes for runSecs seconds                *
 ************************************************************************/
       
        printf("Calculating matgen/dgefa passes for %d seconds\n", (int)runSecs);
        pass = -20;
        ntimes = NTIMES;
        do
        {
            start_time();
            pass = pass + 1;        
            for ( i = 0 ; i < ntimes ; i++)
            {
                matgen(a,lda,n,b,&norma);
                dgefa(a,lda,n,ipvt,&info );
            }
            end_time();
            time2 = secs;
            printf("%10d times %6.2f seconds\n", ntimes, time2);
            if (time2 > runSecs)
            {
                pass = 0;
            }
            if (pass < 0)
            {
                if (time2 < 0.1)
                {
                    ntimes = ntimes * 10;
                }
                else
                {
                    ntimes = ntimes * 2;
                }
            }
        }
        while (pass < 0);
        
        ntimes =  (int)(runSecs * (double)ntimes / time2);
        if (ntimes == 0) ntimes = 1;

        printf("Passes used %10d \n\n", ntimes);
        printf("Times for array with leading dimension of%4d\n\n",lda);
        printf("      dgefa      dgesl      total     Mflops       unit");
        printf("      ratio\n");        

/************************************************************************
 *                              Execute 5 passes                        *
 ************************************************************************/
      
        tm2 = ntimes * overhead1;
        atime[3][6] = 0;

        for (j=1 ; j<6 ; j++)
        {
            start_time();
            for (i = 0; i < ntimes; i++)
            {
                matgen(a,lda,n,b,&norma);
                dgefa(a,lda,n,ipvt,&info );
            }
            end_time();
            atime[0][j] = (secs - tm2)/ntimes;

            start_time();              
            for (i = 0; i < ntimes; i++)
            {
                dgesl(a,lda,n,ipvt,b,0);
            }
            end_time();

            atime[1][j] = secs/ntimes;
            total       = atime[0][j] + atime[1][j];
            atime[2][j] = total;
            atime[3][j] = ops/(1.0e6*total);
            atime[4][j] = 2.0/atime[3][j];
            atime[5][j] = total/cray;
            atime[3][6] = atime[3][6] + atime[3][j];
            
            print_time(j);
        }
        atime[3][6] = atime[3][6] / 5.0;
        printf("Average                          %11.2f\n",
                                               (double)atime[3][6]);        
        
        printf("\nCalculating matgen2 overhead\n");

/************************************************************************
 *             Calculate overhead of executing matgen procedure         *
 ************************************************************************/

        start_time();        
        for ( i = 0 ; i < loop ; i++)
        {
            matgen(aa,ldaa,n,b,&norma);    
        }
        end_time();
        overhead2 = secs;
        overhead2 = overhead2 / (double)loop;
        
        printf("Overhead for 1 matgen %12.5f seconds\n\n", overhead2);
        printf("Times for array with leading dimension of%4d\n\n",ldaa);
        printf("      dgefa      dgesl      total     Mflops       unit");
        printf("      ratio\n");

/************************************************************************
 *                              Execute 5 passes                        *
 ************************************************************************/
              
        tm2 = ntimes * overhead2;
        atime[3][12] = 0;

        for (j=7 ; j<12 ; j++)
        {
            start_time();
            for (i = 0; i < ntimes; i++)
            {
                matgen(aa,ldaa,n,b,&norma);
                dgefa(aa,ldaa,n,ipvt,&info  );
            }
            end_time();
            atime[0][j] = (secs - tm2)/ntimes;
            
            start_time();      
            for (i = 0; i < ntimes; i++)
            {
                dgesl(aa,ldaa,n,ipvt,b,0);
            }
            end_time();
            atime[1][j] = secs/ntimes;
            total       = atime[0][j] + atime[1][j];
            atime[2][j] = total;
            atime[3][j] = ops/(1.0e6*total);
            atime[4][j] = 2.0/atime[3][j];
            atime[5][j] = total/cray;
            atime[3][12] = atime[3][12] + atime[3][j];

            print_time(j);
        }
        atime[3][12] = atime[3][12] / 5.0; 
        printf("Average                          %11.2f\n",
                                              (double)atime[3][12]);  

/************************************************************************
 *           Use minimum average as overall Mflops rating               *
 ************************************************************************/
      
        mflops = atime[3][6];
        if (atime[3][12] < mflops) mflops = atime[3][12];
       
        printf("\n");
        printf( "%s ", ROLLING);
        printf( "%s ", PREC);
        printf(" Precision %11.2f Mflops \n\n",mflops);


    max1 = 0;
    for (i=1 ; i<6 ; i++)
    {
        if (atime[3][i] > max1) max1 = atime[3][i];                 
    }

    max2 = 0;
    for (i=7 ; i<12 ; i++)
    {                 
        if (atime[3][i] > max2) max2 = atime[3][i];                 
    }
    if (max1 < max2) max2 = max1;
   
    sprintf(was[0], "%16.1f",(double)residn);
    sprintf(was[1], "%16.8e",(double)resid);
    sprintf(was[2], "%16.8e",(double)epsn);
    sprintf(was[3], "%16.8e",(double)x1);
    sprintf(was[4], "%16.8e",(double)x2);

/*
    //  Values for Watcom

    sprintf(expect[0], "             0.4");
    sprintf(expect[1], " 7.41628980e-014");
    sprintf(expect[2], " 1.00000000e-015");
    sprintf(expect[3], "-1.49880108e-014");
    sprintf(expect[4], "-1.89848137e-014");
    // Values for Visual C++

    sprintf(expect[0], "             1.7");
    sprintf(expect[1], " 7.41628980e-014");
    sprintf(expect[2], " 2.22044605e-016");
    sprintf(expect[3], "-1.49880108e-014");
    sprintf(expect[4], "-1.89848137e-014");

    // Values for Ubuntu GCC 32 Bit

    sprintf(expect[0], "             1.9");
    sprintf(expect[1], "  8.39915160e-14");
    sprintf(expect[2], "  2.22044605e-16");
    sprintf(expect[3], " -6.22835117e-14");
    sprintf(expect[4], " -4.16333634e-14");
*/

     // Values for Ubuntu GCC 32 Bit

    sprintf(expect[0], "             1.7");
    sprintf(expect[1], "  7.41628980e-14");
    sprintf(expect[2], "  2.22044605e-16");
    sprintf(expect[3], " -1.49880108e-14");
    sprintf(expect[4], " -1.89848137e-14");

    sprintf(title[0], "norm. resid");
    sprintf(title[1], "resid      ");
    sprintf(title[2], "machep     ");
    sprintf(title[3], "x[0]-1     ");
    sprintf(title[4], "x[n-1]-1   ");

    if (strtol(opt, NULL, 10) == 0)
    {
        sprintf(expect[2], " 8.88178420e-016");
    }
    errors = 0;

    printf ("\n");
}