__attribute__((used)) static char *
status_to_str (int status)
{
  static char buf[64];

  if (WIFSTOPPED (status))
    snprintf (buf, sizeof (buf), "%s (stopped)",
	      strsignal (WSTOPSIG (status)));
  else if (WIFSIGNALED (status))
    snprintf (buf, sizeof (buf), "%s (terminated)",
	      strsignal (WSTOPSIG (status)));
  else
    snprintf (buf, sizeof (buf), "%d (exited)", WEXITSTATUS (status));

  return buf;
}