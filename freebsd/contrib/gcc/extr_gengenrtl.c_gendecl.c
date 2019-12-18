__attribute__((used)) static void
gendecl (const char *format)
{
  const char *p;
  int i, pos;

  printf ("extern rtx gen_rtx_fmt_%s\t (RTX_CODE, ", format);
  printf ("enum machine_mode mode");

  /* Write each parameter that is needed and start a new line when the line
     would overflow.  */
  for (p = format, i = 0, pos = 75; *p != 0; p++)
    if (*p != '0')
      {
	int ourlen = strlen (type_from_format (*p)) + 6 + (i > 9);

	printf (",");
	if (pos + ourlen > 76)
	  printf ("\n\t\t\t\t      "), pos = 39;

	printf (" %sarg%d", type_from_format (*p), i++);
	pos += ourlen;
      }

  printf (");\n");
}