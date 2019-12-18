__attribute__((used)) static void t7() {
    struct tag7 { int a; int b; } x;
    struct tag7 *p = &x;
    x.b = 71;
    expect(71, (*p).b);
}