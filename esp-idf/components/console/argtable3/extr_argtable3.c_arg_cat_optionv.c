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

/* Variables and functions */
 int /*<<< orphan*/  arg_cat (char**,char const*,size_t*) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,size_t) ; 

__attribute__((used)) static
void arg_cat_optionv(char *dest,
                     size_t ndest,
                     const char *shortopts,
                     const char *longopts,
                     const char *datatype,
                     int optvalue,
                     const char *separator)
{
    separator = separator ? separator : "";

    if (shortopts)
    {
        const char *c = shortopts;
        while(*c)
        {
            /* "-a|-b|-c" */
            char shortopt[3];

            /* note: shortopt array[] is initialiazed dynamically here to satisfy */
            /* a deficiency in the watcom compiler wrt static array initializers. */
            shortopt[0] = '-';
            shortopt[1] = *c;
            shortopt[2] = 0;

            arg_cat(&dest, shortopt, &ndest);
            if (*++c)
                arg_cat(&dest, separator, &ndest);
        }
    }

    /* put separator between long opts and short opts */
    if (shortopts && longopts)
        arg_cat(&dest, separator, &ndest);

    if (longopts)
    {
        const char *c = longopts;
        while(*c)
        {
            size_t ncspn;

            /* add "--" tag prefix */
            arg_cat(&dest, "--", &ndest);

            /* add comma separated option tag */
            ncspn = strcspn(c, ",");
            strncat(dest, c, (ncspn < ndest) ? ncspn : ndest);
            c += ncspn;

            /* add given separator in place of comma */
            if (*c == ',')
            {
                arg_cat(&dest, separator, &ndest);
                c++;
            }
        }
    }

    if (datatype)
    {
        if (longopts)
            arg_cat(&dest, "=", &ndest);
        else if (shortopts)
            arg_cat(&dest, " ", &ndest);

        if (optvalue)
        {
            arg_cat(&dest, "[", &ndest);
            arg_cat(&dest, datatype, &ndest);
            arg_cat(&dest, "]", &ndest);
        }
        else
            arg_cat(&dest, datatype, &ndest);
    }
}