__attribute__((used)) static void
center_label(char *buffer, int longest, const char *label)
{
    int len = dlg_count_columns(label);
    int left = 0, right = 0;

    *buffer = 0;
    if (len < longest) {
	left = (longest - len) / 2;
	right = (longest - len - left);
	if (left > 0)
	    sprintf(buffer, "%*s", left, " ");
    }
    strcat(buffer, label);
    if (right > 0)
	sprintf(buffer + strlen(buffer), "%*s", right, " ");
}